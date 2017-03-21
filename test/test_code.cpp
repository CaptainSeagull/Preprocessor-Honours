int main(int argc, char **argv) {
    System::String ^s = "Hello World";

    // Prints "String Hello World
    System::Console::WriteLine("{0} {1}", s->GetType(), s);

    return(0);
}
