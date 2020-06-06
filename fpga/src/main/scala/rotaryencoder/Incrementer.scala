package rotaryencoder
import chisel3._

class Incrementer(bitWidth: Int) extends Module {
    val io = IO(new Bundle() {
        val enable = Input(Bool())
        val increment = Input(Bool())
        val value = Output(SInt(bitWidth.W))
    })

    val counter = RegInit(SInt(bitWidth.W), 0.S)

    when(io.enable) {
        when(io.increment) {
            counter := counter + 1.S
        } otherwise {
            counter := counter - 1.S
        }
    }

    io.value := counter
}
