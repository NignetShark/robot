package spi2ssp

import chisel3.iotesters
import chisel3.iotesters.{ChiselFlatSpec, PeekPokeTester}

class SPI2SSPTester(spissp: SPI2SSP) extends PeekPokeTester(spissp)  {

    def impulsion(length : Int = 50): Unit = {
        poke(spissp.io.csIn, false)
        step(50)
        poke(spissp.io.csIn, true)
        step(length)
        poke(spissp.io.csIn, false)
        step(50)
    }

    poke(spissp.io.csIn, true)
    step(100)
    impulsion()
    impulsion()
    impulsion()
    poke(spissp.io.csIn, true)
    step(100)
}


class RotaryEncoderFlatSpec extends ChiselFlatSpec  {
    "using --backend-name verilator" should "be an alternative way to run using verilator" in {
        iotesters.Driver.execute(Array("--target-dir", "VerilatorTest/SPI2SSP",
            "--backend-name", "verilator"), () => new SPI2SSP(1)) {
            c => new SPI2SSPTester(c)
        } should be(true)
    }
}
