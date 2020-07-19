package ultrasonicsensor

import chisel3.iotesters
import chisel3.iotesters.{ChiselFlatSpec, PeekPokeTester}

class MicrosecondsWaiterTester(waiter: MicrosecondsWaiter) extends PeekPokeTester(waiter) {
    def waitUs(delayUs: Int): Unit = {
        for(_ <- 0 until delayUs) {
            step(waiter.usClock.CLOCK_FREQUENCY_MHZ)
        }
    }

    def waitUntilTop(): Int = {
        var count = 0
        while (peek(waiter.io.top) == 0) {
            step(1)
            count += 1
        }
        count
    }

    poke(waiter.io.set, true)
    poke(waiter.io.delay, 2)
    step(1)
    poke(waiter.io.set, false)
    waitUs(10)
    /*poke(waiter.io.delay, 0)
    println("Nombre de tick réel : " + waitUntilTop())
    poke(waiter.io.set, true)
    poke(waiter.io.delay, 1)
    step(1)
    poke(waiter.io.set, false)
    poke(waiter.io.delay, 0)
    println("Nombre de tick réel : " + waitUntilTop())
    */
}

class MicrosecondsWaiterFlatSpec extends ChiselFlatSpec  {
    val maxDelayUs = 2

    "using --backend-name verilator" should "be an alternative way to run using verilator" in {
        iotesters.Driver.execute(Array("--target-dir", "VerilatorTest/MicrosecondsWaiter",
            "--backend-name", "verilator"), () => new MicrosecondsWaiter(maxDelayUs)) {
            c => new MicrosecondsWaiterTester(c)
        } should be(true)
    }
}
