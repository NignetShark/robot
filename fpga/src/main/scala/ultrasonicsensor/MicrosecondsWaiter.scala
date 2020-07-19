package ultrasonicsensor

import chisel3._
import chisel3.util._

class MicrosecondsWaiter(maxDelayUs : Int) extends Module{

    val io = IO(new Bundle {
        val set = Input(Bool())
        val delay = Input(UInt((log2Ceil(maxDelayUs) + 1).W))
        val top = Output(Bool())
        val currentDelay = Output(UInt((log2Ceil(maxDelayUs) + 1).W))
    })

    //val idle :: count :: endCount :: Nil = Enum(3)

    val usClock = Module(new MicrosecondsTop())
    val counter = RegInit(UInt((log2Ceil(maxDelayUs) + 1).W), 0.U)
    val target = RegInit(UInt((log2Ceil(maxDelayUs) + 1).W), 0.U)
    //val state = RegInit(idle)

    when(usClock.io.top) {
        // Increment counterUs until 1 µs passes.
        counter := counter + 1.U
    }

    when(io.set) {
        counter := 0.U
        target := io.delay
    }

    io.currentDelay := counter
    io.top := (counter === target)
    usClock.io.set := io.set || io.top
}

class MicroWaiter(maxDelayUs : Int) {
    val microsecondsWaiter = Module(new MicrosecondsWaiter(maxDelayUs))
    microsecondsWaiter.io.set := false.B
    microsecondsWaiter.io.delay := 0.U

    def set(delay : Int): Unit = {
        microsecondsWaiter.io.set := true.B
        microsecondsWaiter.io.delay := delay.U
    }

    def isEnded(): Bool = {
        microsecondsWaiter.io.top
    }

    def getDelay(): UInt = {
        microsecondsWaiter.io.currentDelay
    }
}