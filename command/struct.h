
struct command
{
	struct {
		struct simple_command** data;
		unsigned n, cap;
	} simples;
	
	char* redirect_in;
	char* redirect_out;
};
