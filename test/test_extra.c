#include "../include/bmi_extensions.h"
#include "test_bmi_c/include/bmi_test_bmi_c.h"
//TODO include unity submodule and/or header and source
#include <unity.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_create_extra()
{
    Extension* extension = (Extension *) malloc(sizeof(Extension));
    TEST_ASSERT_NOT_NULL(extension);
    Bmi_extra* extra = (Bmi_extra*) create_extension(extension, EXTRA);
    TEST_ASSERT_NOT_NULL(extra);
    TEST_ASSERT_EQUAL(extension->type, EXTRA);
    TEST_ASSERT_NOT_NULL(extra->get_extension_version);
    char* version = extra->get_extension_version();
    static char* expected = "v0.0.0";
    char msg [1024];
    version_message_helper("Extra", expected, version, msg);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(version, expected, msg);
    free(extension);
}

void test_extra_1(){

    //Create a BMI model instance
    Bmi *model = (Bmi *) malloc(sizeof(Bmi));
    //test_bmi_c model register
    register_bmi(model);

    /*
     * Method 1 of constructing a generic, centrally mangaged extension
     * 
     * A general, "central management" approach to enumerating supported
     * extension types and abstracting them through a single interface.
     */
    Extension* extension = (Extension *) malloc(sizeof(Extension));
    TEST_ASSERT_NOT_NULL(extension);
    Bmi_extra* extra = (Bmi_extra*) create_extension(extension, EXTRA);
    TEST_ASSERT_NOT_NULL(extra);
    TEST_ASSERT_EQUAL(extension->type, EXTRA);
    register_bmi_extension(extension);
    TEST_ASSERT_NOT_NULL(extra->get_extra);

    int val = -1, ret = -1;
    ret = extra->get_extra(model, &val);

    TEST_ASSERT_EQUAL_INT(222, val);
    TEST_ASSERT_EQUAL_INT(BMI_SUCCESS, ret);
    free(extension);
    free(model);
}

void test_extra_2(){
    /*
     * Method 2 of constructing an a-priori known extension type using
     * explicit casting of type-erased extension
     * 
     * Again, just cause you CAN, doen't mean you SHOULD.
     * This concept may have some very specific use cases where it would be
     * useful, but in general, a lot can go wrong if the types aren't used
     * correctly, and do to it correctly, still likely requires some type
     * of managed ENUM of types to cast
     */
    //Create a BMI model instance
    Bmi *model = (Bmi *) malloc(sizeof(Bmi));
    //test_bmi_c model register
    register_bmi(model);
    
    Extension extension;
    register_bmi_extension2(&extension);
    TEST_ASSERT_NOT_NULL(extension.ext);
    TEST_ASSERT_EQUAL(extension.type, EXTRA);
    //We know from extension.type that this is a Bmi_extra, cast the pointer
    Bmi_extra* extra = (Bmi_extra*)extension.ext;
    TEST_ASSERT_NOT_NULL(extra); //shouldn't be if tmp.ext isn't NULL

    int val = -1, ret = -1;
    ret = extra->get_extra(model, &val);

    TEST_ASSERT_EQUAL_INT(222, val);
    TEST_ASSERT_EQUAL_INT(BMI_SUCCESS, ret);
    free(model);
}

void test_extra_3(){
    /*
     * Method 3 of constructing a stand alone bmi extension structure
     * using an explicit registration function for that extension
     * 
     * This method puts the burden of function hooks on the model, similar
     * to traditional BMI.
     * 
     * I like this for "stand alone" extension implementation/development
     */
    //Create a BMI model instance
    Bmi *model = (Bmi *) malloc(sizeof(Bmi));
    //test_bmi_c model register
    register_bmi(model);
    

    Bmi_extra extra;
    int success = BMI_FAILURE;
    success = register_extra_bmi(&extra);
    TEST_ASSERT_EQUAL(success, BMI_SUCCESS);
    TEST_ASSERT_NOT_NULL(extra.get_extra);

    int val = -1, ret = -1;
    ret = extra.get_extra(model, &val);

    TEST_ASSERT_EQUAL_INT(222, val);
    TEST_ASSERT_EQUAL_INT(BMI_SUCCESS, ret);
    free(model);
}

void test_extra_4(){
    /*
     * Method 4 of constructing an extension model where the caller is responsible
     * for hooking the function pointer to a KNOWN function symbol exposed in the public
     * API of the BMI model, but not via the bmi structure
     * 
     * Probably not a great idea, requires the public model API to expose functionality outside
     * the extension mechanisms.
     */
    //Create a BMI model instance
    Bmi *model = (Bmi *) malloc(sizeof(Bmi));
    //test_bmi_c model register
    register_bmi(model);

    Bmi_extra extra;
    extra.get_extra = get_extra_2;
    
    int val = -1, ret = -1;
    ret = extra.get_extra(model, &val);

    TEST_ASSERT_EQUAL_INT(222, val);
    TEST_ASSERT_EQUAL_INT(BMI_SUCCESS, ret);
    free(model);
}

void test_extra_5(){
    /*
     * Method 5 of constructing an extension model where the linker is used
     * to hook the function pointer from the model to the struct.  Also requires
     * a centralized definition of supported extension types, but only the
     * create_extension function is required, and the function doesn't have
     * to be exposed in the public model header.
     * 
     * This requires a model to implement the EXACT function name of the extension
     * function.  See potential considerations in bmi_extensions.c
     */
    //Create a BMI model instance
    Bmi *model = (Bmi *) malloc(sizeof(Bmi));
    //test_bmi_c model register
    register_bmi(model);

    Extension* extension = (Extension *) malloc(sizeof(Extension));
    TEST_ASSERT_NOT_NULL(extension);
    Bmi_extra* extra = (Bmi_extra*) create_extension(extension, EXTRA);
    TEST_ASSERT_NOT_NULL(extra);
    
    int val = -1, ret = -1;
    ret = extra->get_extra(model, &val);

    TEST_ASSERT_EQUAL_INT(111, val);
    TEST_ASSERT_EQUAL_INT(BMI_SUCCESS, ret);
    free(model);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_extra);
    RUN_TEST(test_extra_1);
    RUN_TEST(test_extra_2);
    RUN_TEST(test_extra_3);
    RUN_TEST(test_extra_4);
    RUN_TEST(test_extra_5);
    return UNITY_END();
}