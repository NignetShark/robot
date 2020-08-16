package ultrasonicsensor

import chisel3._
import chisel3.stage.{ChiselGeneratorAnnotation, ChiselStage}
import chisel3.util._

class UltrasonicSensor(
                          val MAX_DELAY_US: Int = 40000, // Approximately the delay for a maximum of 4 meters
                          val TRIGGER_DELAY_US: Int = 10,
                          val CLEAR_DELAY_US: Int = 250,
                          val RESET_DELAY_US: Int = 200
                      ) extends Module
{

    val bitWidth = log2Ceil(MAX_DELAY_US * 50 + 1)
    val arm_timer_clear :: clearing :: arm_timer_trigger :: triggering :: check_echo :: arm_watchdog_echo :: wait_echo :: arm_watchdog_end_echo :: waiting_end_echo :: arm_reset_echo :: resetting_echo :: Nil = Enum(11)
    val stateReg = RegInit(arm_timer_clear)
    val result = RegInit(UInt(bitWidth.W), 0.U)

    val io = IO(new Bundle() {
        val trigger = Output(Bool())
        val echo = Input(Bool())
        val echoDelay = Output(result.cloneType)
        val resetEcho = Output(Bool())

        val start = Input(Bool())
        val state = Output(stateReg.cloneType)
    })

    println("[DEBUG] Echo delay bitwidth is : " + bitWidth)

    val timerReg = RegInit(result.cloneType, 0.U)
    val enableTimer =   (stateReg === clearing) |
                        (stateReg === triggering) |
                        (stateReg === wait_echo) |
                        (stateReg === waiting_end_echo) |
                        (stateReg === resetting_echo)


    // ==== Constants ====
    val TIMEOUT_ECHO_HIGH = 0.U
    val ERROR_TIMEOUT_ECHO_LOW = 1.U
    val ERROR_ECHO_HIGH_DURING_TRIGGER = 2.U

    // ==== Conditions ====
    val timeoutMax      = timerReg === (MAX_DELAY_US * 50).U
    val timeoutTrigger  = timerReg === (TRIGGER_DELAY_US * 50).U
    val timeoutClear    = timerReg === (CLEAR_DELAY_US * 50).U
    val timeoutReset    = timerReg === (RESET_DELAY_US * 50).U

    // ==== Default values ====
    io.trigger := stateReg === triggering
    io.resetEcho := stateReg === resetting_echo
    io.echoDelay := result
    io.state := stateReg

    // ==== State machine logic ====

    when(enableTimer) {
        timerReg := timerReg + 1.U
    } otherwise {
        timerReg := 0.U
    }

    // NOTE : For some obscure reasons the switch statement
    // was making faulty behaviour.


    when(stateReg === arm_timer_clear) {
        when(io.start) {
            stateReg := clearing
        }
    }

    when(stateReg === clearing) { // Wait (clear timing)
        when(timeoutClear) {
            stateReg := arm_timer_trigger
        }
    }

    when(stateReg === arm_timer_trigger) { // Setup waiter to create the trigger
        stateReg := triggering
    }

    when(stateReg === triggering) { // Create trigger signal
        when(timeoutTrigger) {
            stateReg := check_echo
        }
    }

    when(stateReg === check_echo) {
        when(io.echo) {
            result := ERROR_ECHO_HIGH_DURING_TRIGGER
            stateReg := arm_timer_clear
        } .otherwise {
            stateReg := arm_watchdog_echo
        }
    }

    when(stateReg === arm_watchdog_echo) {
        stateReg := wait_echo
    }

    when(stateReg === wait_echo) { // wait the beginning of the echo
        when(io.echo) {
            stateReg := arm_watchdog_end_echo
        }
        when(timeoutMax) {
            result := ERROR_TIMEOUT_ECHO_LOW // timeout
            stateReg := arm_timer_clear
        }
    }

    when(stateReg === arm_watchdog_end_echo) {
        stateReg := waiting_end_echo
    }

    when(stateReg === waiting_end_echo) { // Wait the end of the echo
        when(!io.echo) {
            result := timerReg
            stateReg := arm_timer_clear
        }
        when(timeoutMax) {
            result := TIMEOUT_ECHO_HIGH // timeout
            stateReg := arm_reset_echo
        }
    }

    when(stateReg === arm_reset_echo) {
        stateReg := resetting_echo
    }

    when(stateReg === resetting_echo) {
        when(timeoutReset) {
            stateReg := arm_timer_clear
        }
    }
}

object TopLevel extends App {
    val chiselArgs = Array[String]("--target-dir", "generated")
    (new ChiselStage).execute(chiselArgs, Seq(ChiselGeneratorAnnotation(() => new UltrasonicSensor())))
}
