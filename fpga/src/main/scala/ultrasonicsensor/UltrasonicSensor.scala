package ultrasonicsensor

import chisel3._
import chisel3.stage.{ChiselGeneratorAnnotation, ChiselStage}
import chisel3.util._

class UltrasonicSensor extends Module {
    val MAX_DELAY_US = 40000 // Approximately the delay for a maximum of 4 meters
    val TRIGGER_DELAY_US = 10
    val CLEAR_DELAY_US = 250

    val io = IO(new Bundle() {
        val trigger = Output(Bool())
        val echo = Input(Bool())
        val echoDelay = Output(UInt((log2Ceil(MAX_DELAY_US) + 1).W))
        val state = Output(UInt(log2Ceil(5).W))
        val top = Output(Bool())
    })

    println("[DEBUG] Echo delay bitwidth is : " + (log2Ceil(MAX_DELAY_US) + 1))

    val arm_timer_trigger :: triggering :: arm_watchdog_echo :: wait_echo :: arm_watchdog_end_echo :: waiting_end_echo :: arm_timer_clear :: clearing :: Nil = Enum(8)

    val result = RegInit(UInt((log2Ceil(MAX_DELAY_US) + 1).W), 0.U)
    val stateReg = RegInit(arm_timer_trigger)
    val waiter = new MicroWaiter(MAX_DELAY_US)

    io.trigger := false.B
    io.echoDelay := result
    io.state := stateReg

    switch(stateReg) {
        is(arm_timer_trigger) { // Setup waiter to create the trigger
            waiter.set(TRIGGER_DELAY_US) // Arm a timeout
            stateReg := triggering
        }
        is(triggering) { // Create trigger signal
            io.trigger := true.B
            when(waiter.isEnded()) {
                stateReg := arm_watchdog_echo
            }
        }
        is(arm_watchdog_echo) {
            waiter.set(MAX_DELAY_US) // Arm a timeout
            stateReg := wait_echo
        }
        is(wait_echo) { // wait the beginning of the echo
            when(io.echo) {
                stateReg := arm_watchdog_end_echo
            }.elsewhen (waiter.isEnded()) {
                result := 0.U // timeout
                stateReg := arm_timer_clear
            }
        }
        is(arm_watchdog_end_echo) {
            //waiter.set(MAX_DELAY_US) // Arm a timeout
            stateReg := waiting_end_echo
        }
        is(waiting_end_echo) { // Wait the end of the echo
            when(!io.echo) {
                result := waiter.getDelay()
                stateReg := arm_timer_clear
            }/*.elsewhen (waiter.isEnded()) {
                result := 0.U // timeout
                stateReg := arm_timer_clear
            }*/
        }
        is(arm_timer_clear) {
            waiter.set(CLEAR_DELAY_US) // Trigger must be 10us long.
            stateReg := clearing
        }
        is(clearing) { // Wait (clear timing)
            when(waiter.isEnded()) {
                stateReg := arm_timer_trigger
            }
        }
    }

    io.top := waiter.isEnded()
}

object TopLevel extends App {
    val chiselArgs = Array[String]("--target-dir", "generated")
    (new ChiselStage).execute(chiselArgs, Seq(ChiselGeneratorAnnotation(() => new UltrasonicSensor())))
}
