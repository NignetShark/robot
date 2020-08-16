package spi2ssp

import chisel3._
import chisel3.stage.{ChiselGeneratorAnnotation, ChiselStage}
import chisel3.util._

class SPI2SSP(maxUsDuration: Int) extends Module {
    val io = IO(new Bundle {
        val csIn = Input(Bool())
        val csOut = Output(Bool())
    })

    val maxNbClock = 50 * maxUsDuration

    val passThrough :: clear :: Nil = Enum(2)
    val stateReg = RegInit(passThrough)
    var counter = RegInit(UInt(log2Ceil(maxNbClock).W), 0.U)

    io.csOut := io.csIn

    switch(stateReg) {
        is(passThrough) {
            when(RegNext(io.csIn) === false.B && io.csIn === true.B) { // Rising edge
                counter := 0.U
                io.csOut := false.B
                stateReg := clear
            }
        }
        is(clear) {
            io.csOut := false.B
            when(counter === (maxNbClock - 1).U) {
                counter := 0.U
                stateReg := passThrough
            } otherwise {
                counter := counter + 1.U
            }
        }
    }


}

object TopLevel extends App {
    val chiselArgs = Array[String]("--target-dir", "generated")
    (new ChiselStage).execute(chiselArgs, Seq(ChiselGeneratorAnnotation(() => new SPI2SSP(1))))
}