package ultrasonicsensor

import chisel3.iotesters
import chisel3.iotesters.{ChiselFlatSpec, PeekPokeTester}

class UltrasonicSensorTester(sensor: UltrasonicSensor) extends PeekPokeTester(sensor) {

    def waitUs(delayUs: Int): Unit = {
        for(_ <- 0 until delayUs) {
            step(50)
        }
    }

    def waitEndOfTrigger(): Unit  = {
        while (peek(sensor.io.trigger) == 0) step(1)
        print("Trigger ... ")
        while (peek(sensor.io.trigger) == 1) step(1)
        println("OK.")
    }

    poke(sensor.io.start, true)
    for(i <- 1 to 3) {

        waitEndOfTrigger()

        waitUs(2)
        step(5)
        poke(sensor.io.echo, true)

        waitUs(i * 10)
        step(5)
        poke(sensor.io.echo, false)

    }
    waitEndOfTrigger()
}

class UltrasonicSensorFlatSpec extends ChiselFlatSpec  {
    "using --backend-name verilator" should "be an alternative way to run using verilator" in {
        iotesters.Driver.execute(Array("--target-dir", "VerilatorTest/UltrasonicSensor",
            "--backend-name", "verilator"), () => new UltrasonicSensor()) {
            c => new UltrasonicSensorTester(c)
        } should be(true)
    }
}
