#include "pch.h"
#include "../analizator/Token.h"

TEST(Token_Test, ConstructorEmpty) {
	std::ostringstream o;
	Token t1(LexemType::eof);
	t1.print(o);
	EXPECT_EQ("[eof]", o.str());
	EXPECT_EQ(LexemType::eof, t1.type());
	EXPECT_EQ(0, t1.value());
	EXPECT_EQ("", t1.str());
}

TEST(Token_Test, ConstructorString) {
	std::ostringstream o;
	Token t1(LexemType::id, "name");
	t1.print(o);
	EXPECT_EQ("[id, \"name\"]", o.str());
	EXPECT_EQ(LexemType::id, t1.type());
	EXPECT_EQ(0, t1.value());
	EXPECT_EQ("name", t1.str());
	o.str("");
	Token t2(LexemType::error, "символьная константа содержит более одного символа");
	t2.print(o);
	EXPECT_EQ("[error, \"символьная константа содержит более одного символа\"]", o.str());
	EXPECT_EQ(LexemType::error, t2.type());
	EXPECT_EQ(0, t2.value());
	EXPECT_EQ("символьная константа содержит более одного символа", t2.str());
}

TEST(Token_Test, ConstructorCharacter) {
	std::ostringstream o;
	Token t('a');
	t.print(o);
	EXPECT_EQ("[chr, 'a']", o.str());
	EXPECT_EQ(LexemType::chr, t.type());
	EXPECT_EQ('a', t.value());
	EXPECT_EQ("", t.str());
}

TEST(Token_Test, ConstructorInteger) {
	std::ostringstream o;
	Token t(42);
	t.print(o);
	EXPECT_EQ("[num, 42]", o.str());
	EXPECT_EQ(LexemType::num, t.type());
	EXPECT_EQ(42, t.value());
	EXPECT_EQ("", t.str());
}