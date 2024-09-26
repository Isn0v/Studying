/** Software implementation of PROC (PROstoy Calculator) mk. 1 (or mk. 2).
  *
  * You should finish this procedure according to the reference described in
  * `README.md` to complete the assignment.
  */
@main def calculator(commands: String*): Unit = {

  /** Converts given string `s` to integer.
    *
    * Throws [[NumberFormatException]] if `s` can't be converted to integer, but
    * you shouldn't worry about it at this moment.
    */
  def parseInt(s: String): Int = s.toInt

  var acc: Int = 0
  var A: Int = 0
  var B: Int = 0
  var blink: Boolean = false
  // val new_commands: Array[String] = Array("20", "2", "*")
  println(commands)

  for (c <- commands) {
    c match {
      case s: String if s.toIntOption.isDefined => {
        blink match {
          case false => A = s.toInt
          case true  => B = s.toInt
        }
        blink = !blink
      }
      case "+" => {
        acc = A + B
        blink = false
      }
      case "-" => {
        acc = A - B
        blink = false
      }
      case "*" => {
        acc = A * B
        blink = false
      }
      case "/" => {
        if (B == 0) {
          acc = 0
          A = 0
          B = 0
          blink = false
        } else {
          acc = A / B
          blink = false
        }
      }
      case "swap" => {
        val tmp = A
        A = B
        B = tmp
      }
      case "blink" => {
        blink = !blink
      }
      case "acc" => {
        blink match {
          case false => A = acc
          case true  => B = acc
        }
        blink = !blink
      }
    }
  }

  println(acc)
}
