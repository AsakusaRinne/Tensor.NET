﻿using CodeGenerator;

var AddGenerator = new BasicArithGenerator() { Name = "Add", Expr = "x + y" };
CodeWriter.Write("Add", AddGenerator.GetCode());

var SubGenerator = new BasicArithGenerator() { Name = "Sub", Expr = "x - y" };
CodeWriter.Write("Sub", SubGenerator.GetCode());

var DivGenerator = new BasicArithGenerator() { Name = "Div", Expr = "x / y" };
CodeWriter.Write("Div", DivGenerator.GetCode());

var ModGenerator = new BasicArithGenerator() { Name = "Mod", Expr = "x % y" };
CodeWriter.Write("Mod", ModGenerator.GetCode());

var AbsGenerator = new BasicFunctionGenerator() { Name = "Abs", Expr = "System.Math.Abs(x)" };
CodeWriter.Write("Abs", AbsGenerator.GetCode());

var FloorGenerator = new BasicFunctionGenerator() { Name = "Floor", Expr = "System.Math.Floor(x)" };
CodeWriter.Write("Floor", FloorGenerator.GetCode());

var CeilGenerator = new BasicFunctionGenerator() { Name = "Ceil", Expr = "System.Math.Ceil(x)" };
CodeWriter.Write("Ceil", CeilGenerator.GetCode());

var RoundGenerator = new BasicFunctionGenerator() { Name = "Round", Expr = "System.Math.Round(x)" };
CodeWriter.Write("Round", RoundGenerator.GetCode());