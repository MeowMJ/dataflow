// RUN: neura-interpreter %s | FileCheck %s

module {
  func.func @test() -> f32 {
    %arg0 = "neura.constant"() {value = 9.0 : f32, predicate = true} : () -> f32
    %cst = "neura.constant"() {value = 2.0 : f32, predicate = false} : () -> f32
    %res = "neura.fadd"(%arg0, %cst) : (f32, f32) -> f32
    return %res : f32
    // CHECK: [neura-interpreter]  → Output: 0.000000
  }
}
