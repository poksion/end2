// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include <cute_end.h>

#include "../main/modules/EStringUtil.h"

using namespace end2;

void test_stringutil() {
    //const char* hhh = "녕";
    //const wchar_t* hhh = L"\uC548\uB155";
    //EFileModule* pFileModule = ESystem::getSystem().getModulePtr<EFileModule>();
    //EXPECT_TRUE(pFileModule != 0);
    //bool bRet = pFileModule->isExistFile("ed://test/index.xml");
    //EXPECT_TRUE(bRet);

    //std::string file_name;
    //pFileModule->getAbsolutePathFromURI(file_name, "ed://test/index.xml");
    //EXml xml_test;
    //xml_test.loadFromFile(file_name.c_str());
    //EXmlHandler handler_test(xml_test, true);
    //std::string ttt;
    //handler_test.getAttribute(ttt, "value");
    ////EStringUtil tUtil("\xEC\x95\x88\xEB\x85\x95");
    //EStringUtil tUtil(ttt);
    //std::wstring h = tUtil.getWStringFromUTF8();
    ////std::wstring h = L"안녕 세상아";
    ////const char* h = "안녕 세상아";
    ////const char *h = "\xc9\x11";

    EStringUtil stringUtil;
    stringUtil.formatStr("Hello {0}st string format", 1);
    ASSERT_EQUAL("Hello 1st string format", stringUtil.getString());

    stringUtil.clearString();
    stringUtil.formatStr("{0} format : {1: 000}", "Numeric", 2);
    ASSERT_EQUAL("Numeric format : 002", stringUtil.getString());

    stringUtil.clearString();
    stringUtil.formatStr("{0} format : {1:000.00}", "Numeric", 2);
    ASSERT_EQUAL("Numeric format : 002.00", stringUtil.getString());

    stringUtil.clearString();
    stringUtil.formatStr("{0} format : { 1: 000.000}", "Numeric", 10403.2352f);
    ASSERT_EQUAL("Numeric format : 10403.235", stringUtil.getString());

    stringUtil.clearString();
    stringUtil.formatStr("{0} format : { 1 :  0000.000000}", "Numeric", (double) 23.23435253);
    ASSERT_EQUAL("Numeric format : 0023.234352", stringUtil.getString());

    stringUtil.clearString();
    stringUtil.formatStr("{1} format : {0: 00.00}", 1.24521f, "Float");
    ASSERT_EQUAL("Float format : 01.24", stringUtil.getString());

    stringUtil.clearString();
    float f = 0.f;
    stringUtil.formatStr("{1} format : {0: 0.00}", f, "Float");
    ASSERT_EQUAL("Float format : 0.00", stringUtil.getString());

    stringUtil.clearString();
    stringUtil.formatStr("{1} {0:0.00} must have index error", 10.3);
    std::string message(EStringUtil::FORMAT_INDEX_ERROR);
    message += " 10.30 must have index error";
    ASSERT_EQUAL(message, stringUtil.getString());

    stringUtil.clearString();
    std::vector<std::string> result;
    EStringUtil::split(result, "a bc def");
    ASSERT_EQUAL("a", result[0]);
    ASSERT_EQUAL("bc", result[1]);
    ASSERT_EQUAL("def", result[2]);
}

CUTE_TEST(test_stringutil);

// vim: ts=4:sw=4
