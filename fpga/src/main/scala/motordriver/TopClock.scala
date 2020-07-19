package motordriver
import chisel3._
import chisel3.util.log2Ceil

class TopClock(val frequency: Int) extends Module {

    val io = IO(new Bundle() {
        val top = Output(Bool())
    })

    val clockFreq = 50000000 // Clock frequency (50MHz)
    val period = clockFreq / frequency
    val counter = RegInit(UInt(log2Ceil(period).W), 0.U)

    when(counter === (period - 1).U) {
        counter := 0.U
        io.top := true.B
    } otherwise {
        io.top := false.B
        counter := counter + 1.U
    }


}
