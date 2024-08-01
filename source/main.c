#include <libtcc.h>

char hello_tcc_script[] =
    "#include <tcclib.h>\n"
    "\n"
    "void hello_tcc() {\n"
    "printf(\"hello, tcc!\");\n"
    "}\n"
    "\n";

int main(int argc, char **argv)
{
    TCCState *tcc_state = tcc_new();
    tcc_set_output_type(tcc_state, TCC_OUTPUT_MEMORY);
    tcc_compile_string(tcc_state, hello_tcc_script);
    tcc_relocate(tcc_state);
    void (*run_exported_hello_tcc)(void) = tcc_get_symbol(tcc_state, "hello_tcc");
    run_exported_hello_tcc();
    tcc_delete(tcc_state);
    return 0;
}