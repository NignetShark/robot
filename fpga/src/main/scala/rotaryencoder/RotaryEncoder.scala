package rotaryencoder

import chisel3._
import chisel3.stage.{ChiselGeneratorAnnotation, ChiselStage}

class RotaryEncoder(bitWidth: Int) extends Module {
    val io = IO(new Bundle() {
        val channelA = Input(Bool())
        val channelB = Input(Bool())
        val position = Output(SInt(bitWidth.W))
    })

    val lastValueChannelA = RegNext(io.channelA)
    val lastValueChannelB = RegNext(io.channelB)

    val incrementer = Module(new Incrementer(bitWidth))
    val enable = RegInit(Bool(), false.B)
    val increment = RegInit(Bool(), true.B)

    enable := false.B

    // Channel A rising edge
    when(io.channelA && !lastValueChannelA) {
        enable := true.B
        increment := !io.channelB
    }

    // Channel A falling edge
    when(!io.channelA && lastValueChannelA) {
        enable := true.B
        increment := io.channelB
    }

    // Channel B rising edge
    when(io.channelB && !lastValueChannelB) {
        enable := true.B
        increment := io.channelA
    }

    // Channel B falling edge
    when(!io.channelB && lastValueChannelB) {
        enable := true.B
        increment := !io.channelA
    }

    incrementer.io.increment := increment
    incrementer.io.enable := enable
    io.position := incrementer.io.value
}


object TopLevel extends App {
    val bitWidth = 32
    val chiselArgs = Array[String]("--target-dir", "generated")
    (new ChiselStage).execute(chiselArgs, Seq(ChiselGeneratorAnnotation(() => new RotaryEncoder(bitWidth))))
}