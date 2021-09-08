#include "parser.h"
#include "asura.h"

int main(int argc, char *argv[])
{
	Parser parser;
	Program *pgm;
	ParsingError pe;

	if (argc>1) {
		parser.Open(argv[1]);
		pgm = parser.ParseProgram();
		if (!pgm) {
			pe = parser.GetLastError();
			printf("%d\n", pe.position);
		}
		else printProgram(pgm);
	}
}
