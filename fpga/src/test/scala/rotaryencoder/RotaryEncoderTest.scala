package rotaryencoder

import chisel3.iotesters
import chisel3.iotesters.{ChiselFlatSpec, Driver, PeekPokeTester}

class RotaryEncoderTester(encoder: RotaryEncoder) extends PeekPokeTester(encoder)  {
    val CLOCK_PERIOD = 4
    assert(CLOCK_PERIOD % 4 == 0, "The clock period must be divisible by 4")

    def forwardOnePeriod(): Unit = {
        for(i <- 0  until CLOCK_PERIOD) {
            poke(encoder.io.channelA, i < CLOCK_PERIOD / 2)
            poke(encoder.io.channelB, i >= CLOCK_PERIOD / 4 && i < 3 * CLOCK_PERIOD / 4)
            step(1)
        }
    }

    def backwardOnePeriod(): Unit = {
        for(i <- 0  until CLOCK_PERIOD) {
            poke(encoder.io.channelB, i < CLOCK_PERIOD / 2)
            poke(encoder.io.channelA, i >= CLOCK_PERIOD / 4 && i < 3 * CLOCK_PERIOD / 4)
            step(1)
        }
    }

    for(_ <- 0 until 4) {
        forwardOnePeriod();
    }

    for(_ <- 0 until 4) {
        backwardOnePeriod();
    }
}


class RotaryEncoderFlatSpec extends ChiselFlatSpec  {
    val bitWidth = 6

    "using --backend-name verilator" should "be an alternative way to run using verilator" in {
        iotesters.Driver.execute(Array("--target-dir", "VerilatorTest/RotaryEncoder",
            "--backend-name", "verilator"), () => new RotaryEncoder(bitWidth)) {
            c => new RotaryEncoderTester(c)
        } should be(true)
    }
}
