package buzzer

import chisel3._
import chisel3.util._

class Buzzer() extends Module {
    val io = IO(new Bundle {
        val freq = Input(UInt(8.W))
        val output = Output(Bool())
    })
}
