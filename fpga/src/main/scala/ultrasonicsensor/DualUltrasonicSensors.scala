package ultrasonicsensor

import chisel3._
import chisel3.stage.{ChiselGeneratorAnnotation, ChiselStage}
import chisel3.util._

class DualUltrasonicSensors(
                               val MAX_DELAY_US: Int = 50000, // Approximately the delay for a maximum of 4 meters
                               val TRIGGER_DELAY_US: Int = 20,
                               val CLEAR_DELAY_US: Int = 1000,
                               val RESET_DELAY_US: Int = 200
                           ) extends Module
{
    val sonarA = Module(new UltrasonicSensor(MAX_DELAY_US, TRIGGER_DELAY_US, CLEAR_DELAY_US, RESET_DELAY_US))
    val sonarB = Module(new UltrasonicSensor(MAX_DELAY_US, TRIGGER_DELAY_US, CLEAR_DELAY_US, RESET_DELAY_US))
    val startA :: waitA :: startB :: waitB :: Nil = Enum(4)
    val stateReg = RegInit(startA)

    val stateDebug = Cat(stateReg, sonarA.io.state, sonarB.io.state)

    val io = IO(new Bundle() {
        val triggerA = Output(Bool())
        val echoA = Input(Bool())
        val echoDelayA = Output(sonarA.io.echoDelay.cloneType)
        val resetEchoA = Output(Bool())

        val triggerB = Output(Bool())
        val echoB = Input(Bool())
        val echoDelayB = Output(sonarB.io.echoDelay.cloneType)
        val resetEchoB = Output(Bool())

        val state = Output(stateDebug.cloneType)
    })

    io.triggerA := sonarA.io.trigger
    sonarA.io.echo := io.echoA
    io.echoDelayA := sonarA.io.echoDelay
    io.resetEchoA := sonarA.io.resetEcho
    sonarA.io.start := false.B
    io.triggerB := sonarB.io.trigger
    sonarB.io.echo := io.echoB
    io.echoDelayB := sonarB.io.echoDelay
    io.resetEchoB := sonarB.io.resetEcho
    sonarB.io.start := false.B
    io.state := stateDebug

    val readyA = sonarA.io.state === sonarA.arm_timer_clear
    val readyB = sonarB.io.state === sonarB.arm_timer_clear

    switch(stateReg) {
        is(startA) {
            when(readyA) {
                sonarA.io.start := true.B
                stateReg := waitA
            }
        }
        is(waitA) {
            when(readyA) {
                stateReg := startB
            }
        }
        is(startB) {
            when(readyB) {
                sonarB.io.start := true.B
                stateReg := waitB
            }
        }
        is(waitB) {
            when(readyB) {
                stateReg := startA
            }
        }
    }

}

object TopLevelDual extends App {
    val chiselArgs = Array[String]("--target-dir", "generated")
    (new ChiselStage).execute(chiselArgs, Seq(ChiselGeneratorAnnotation(() => new DualUltrasonicSensors())))
}
