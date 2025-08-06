// RUN: neura-interpreter %s | FileCheck %s

func.func @test_store_load_i32() -> i32 {
  %addr = arith.constant 0 : i32       
  %val = arith.constant 123 : i32
  "neura.store"(%val, %addr) : (i32, i32) -> ()
  %loaded = "neura.load"(%addr) : (i32) -> i32
  // CHECK: [neura-interpreter]  → Output: 123.000000
  return %loaded : i32
}

func.func @test_store_load_f32() -> f32 {
  %addr = arith.constant 4 : i32         
  %val = arith.constant 3.14 : f32
  "neura.store"(%val, %addr) : (f32, i32) -> ()
  %loaded = "neura.load"(%addr) : (i32) -> f32
  // CHECK: [neura-interpreter]  → Output: 3.140000
  return %loaded : f32
}