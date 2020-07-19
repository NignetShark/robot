package motordriver

import chisel3.iotesters
import chisel3.iotesters.{ChiselFlatSpec, PeekPokeTester}

class MotorDriverTest(dut: MotorDriver) extends PeekPokeTester(dut) {
    for(order <- 0 until 16) {
        poke(dut.io.order, order)
        step(32 * 10)
    }
}

class MotorDriverFlatSpec extends ChiselFlatSpec  {

    "using --backend-name verilator" should "be an alternative way to run using verilator" in {
        iotesters.Driver.execute(Array("--target-dir", "VerilatorTest/MotorDriver",
            "--backend-name", "verilator"), () => new MotorDriver(1000000, 16)) {
            c => new MotorDriverTest(c)
        } should be(true)
    }

    "using --backend-name firrtl" should "be an alternative way to run using verilator" in {
        iotesters.Driver.execute(Array("--target-dir", "VerilatorTest/MotorDriver/FIRRTL",
            "--backend-name", "firrtl", "--fint-write-vcd"), () => new MotorDriver(1000000, 16)) {
            c => new MotorDriverTest(c)
        } should be(true)
    }
}
