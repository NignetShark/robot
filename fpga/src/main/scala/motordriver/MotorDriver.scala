package motordriver

import chisel3._
import chisel3.stage.{ChiselGeneratorAnnotation, ChiselStage}
import chisel3.util.{isPow2, log2Ceil}

class MotorDriver(pwmFrequency: Int, accuracy: Int) extends Module {
    require(isPow2(accuracy), "The accuracy must be a power of 2")

    val io = IO(new Bundle() {
        val order = Input(UInt(log2Ceil(accuracy).W))
        val forward = Input(Bool())
        val in1 = Output(Bool())
        val in2 = Output(Bool())
    })

    val topClock = Module(new TopClock(pwmFrequency * accuracy))
    val counter = RegInit(UInt(log2Ceil(accuracy).W), 0.U)
    val pwm = WireInit(counter < io.order)


    when(topClock.io.top) {
        counter := counter + 1.U
    }

    when(io.forward) {
        io.in1 := pwm
        io.in2 := false.B
    } otherwise {
        io.in1 := false.B
        io.in2 := pwm
    }
}

object TopLevel extends App {
    val chiselArgs = Array[String]("--target-dir", "generated")
    (new ChiselStage).execute(chiselArgs, Seq(ChiselGeneratorAnnotation(() => new MotorDriver(10000, 256))))
}
