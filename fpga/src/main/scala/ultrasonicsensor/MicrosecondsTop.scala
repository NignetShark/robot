package ultrasonicsensor

import chisel3._
import chisel3.util.log2Ceil

class MicrosecondsTop extends Module {
    val CLOCK_FREQUENCY_MHZ = 50

    val io = IO(new Bundle() {
        val set = Input(Bool())
        val top = Output(Bool())
    })

    val value = RegInit(UInt(log2Ceil(CLOCK_FREQUENCY_MHZ).W), 0.U)
    value := value + 1.U
    io.top := value === (CLOCK_FREQUENCY_MHZ - 1).U
    when (io.set || io.top) { value := 0.U }
}
