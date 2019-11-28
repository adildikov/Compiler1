#include "pch.h"
#include "../analizator/Scaner.h"
#include "../analizator/Token.h"


TEST(ScannerTests, EmptyFile) {
	std::istringstream iss("");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InvalidCharacter) {
	std::istringstream iss("кот");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, DigitTest) {
	std::istringstream iss("5");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(5, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}


TEST(ScannerTests, NumberTest) {
	std::istringstream iss("42");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(42, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, DigitCommaTest) {
	std::istringstream iss("5;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(5, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, TwoNumbersTest) {
	std::istringstream iss("5;42");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(5, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(42, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InvalidCharacterTest) {
	std::istringstream iss("'ab'");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, EmptyCharacterTest) {
	std::istringstream iss("''");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, KeywordTest) {
	std::istringstream iss("return;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwreturn, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IdTest) {
	std::istringstream iss("myVar1");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("myVar1", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, KeywordAndIdTest) {
	std::istringstream iss("return myVar1;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwreturn, token.type());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("myVar1", token.str());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, StringTest) {
	std::istringstream iss("\"Hello world!\"");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::str, token.type());
	EXPECT_EQ("Hello world!", token.str());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, StringUnexpectedEOFTest) {
	std::istringstream iss("\"Oh no, stream end");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, MinusCharacterTest) {
	std::istringstream iss("-");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opminus, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusNumCharacterTest) {
	std::istringstream iss("-4");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(-4, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusNum2CharacterTest) {
	std::istringstream iss("-10");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(-10, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusNum3CharacterTest) {
	std::istringstream iss("-12");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(-12, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusTwoNumCharacterTest) {
	std::istringstream iss("12 - 19");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(12, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opminus, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(19, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}
// ???
//	TEST(ScannerTests, MinusTwoNumCharacterTest) {
//		std::istringstream iss("12-19");
//		Scanner scanner(iss);
//		Token token = scanner.getNextToken();
//		token.print(std::cerr);
//		ASSERT_EQ(LexemType::num, token.type());
//		ASSERT_EQ(12, token.value());
//		token = scanner.getNextToken();
//		token.print(std::cerr);
//		ASSERT_EQ(LexemType::opminus, token.type());
//		token = scanner.getNextToken();
//		token.print(std::cerr);
//		ASSERT_EQ(LexemType::num, token.type());
//		ASSERT_EQ(19, token.value());
//		token = scanner.getNextToken();
//		token.print(std::cerr);
//		ASSERT_EQ(LexemType::eof, token.type());
//	}
// ???

TEST(ScannerTests, MinusTwoNum2CharacterTest) {
	std::istringstream iss("12 + (-19)");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(12, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opplus, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(-19, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, NotCharacterTest) {
	std::istringstream iss("!");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opnot, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, NeCharacterTest) {
	std::istringstream iss("!=");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opne, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, LtCharacterTest) {
	std::istringstream iss("<");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::oplt, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, LeCharacterTest) {
	std::istringstream iss("<=");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::ople, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IncCharacterTest) {
	std::istringstream iss("+");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opplus, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, NumIncCharacterTest) {
	std::istringstream iss("5++");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opinc, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OrCharacterTest) {
	std::istringstream iss("||");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opor, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InvalidOrCharacterTest) {
	std::istringstream iss("|'a'");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, AndCharacterTest) {
	std::istringstream iss("&&");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opand, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InvalidAndCharacterTest) {
	std::istringstream iss("&8");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, IfCharacterTest) {
	std::istringstream iss("if");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwif, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IfSignCharacterTest) {
	std::istringstream iss("if (a==10);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwif, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opeq, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(10, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ForCharacterTest) {
	std::istringstream iss("for");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwfor, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ForSignCharacterTest) {
	std::istringstream iss("for (i=1;i<7;i++)");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwfor, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("i", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(1, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("i", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::oplt, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(7, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("i", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opinc, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SwitchCharacterTest) {
	std::istringstream iss("switch");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwswitch, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SwitchSignCharacterTest) {
	std::istringstream iss("switch (c*14);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwswitch, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("c", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opmult, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(14, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutCharacterTest) {
	std::istringstream iss("out");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutNumCharacterTest) {
	std::istringstream iss("out(56);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(56, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);;
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutACharacterTest) {
	std::istringstream iss("out(result);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("result", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutHWCharacterTest) {
	std::istringstream iss("out(\"Hello there!\");");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::str, token.type());
	EXPECT_EQ("Hello there!", token.str());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InCharacterTest) {
	std::istringstream iss("in");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwin, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, WhileCharacterTest) {
	std::istringstream iss("while");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwwhile, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, WhileSignCharacterTest) {
	std::istringstream iss("while (a<=25);");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwwhile, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::ople, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(25, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CaseCharacterTest) {
	std::istringstream iss("case");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwcase, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ElseCharacterTest) {
	std::istringstream iss("else");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwelse, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, BracketCharacterTest) {
	std::istringstream iss("[]");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ColonCharacterTest) {
	std::istringstream iss(":");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::colon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CommaCharacterTest) {
	std::istringstream iss(",");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ParCharacterTest) {
	std::istringstream iss("()");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, BraceCharacterTest) {
	std::istringstream iss("{}");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lbrace, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rbrace, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IntCharacterTest) {
	std::istringstream iss("int f;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("f", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MoreOneIntCharacterTest) {
	std::istringstream iss("int a=0,b=1,c=2;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(0, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("b", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(1, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("c", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(2, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharCharacterTest) {
	std::istringstream iss("char a;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MoreOneCharCharacterTest) {
	std::istringstream iss("char a,b,c;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("b", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::comma, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("c", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SignCharacterTest) {
	std::istringstream iss("=");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharsignCharacterTest) {
	std::istringstream iss("char a=10;");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(10, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IntMasCharacterTest) {
	std::istringstream iss("int a[1];");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("a", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(1, token.value());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharMasCharacterTest) {
	std::istringstream iss("char mas[] = \"abcdef\";");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("mas", token.str());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::str, token.type());
	EXPECT_EQ("abcdef", token.str());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, GtPlusNotStatementTest) {
	std::istringstream iss("1+54>!a");
	Scanner scanner(iss);
	Token token = scanner.getNextToken();
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(1, token.value());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opplus, token.type());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::num, token.type());
	EXPECT_EQ(54, token.value());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opgt, token.type());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::opnot, token.type());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::id, token.type());
	EXPECT_EQ("a", token.str());
	scanner >> token;
	token.print(std::cerr);
	EXPECT_EQ(LexemType::eof, token.type());
}