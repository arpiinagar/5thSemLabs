#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

const char *keywords[] = {"auto",   "break",    "case",    "char",   "continue",
                          "do",     "default",  "const",   "double", "else",
                          "enum",   "extern",   "for",     "if",     "include",
                          "goto",   "float",    "int",     "long",   "register",
                          "return", "signed",   "static",  "sizeof", "short",
                          "struct", "switch",   "typedef", "union",  "void",
                          "while",  "volatile", "unsigned", "bool", "true", "false", "printf", "scanf"
                         };

const char *dtypes[] = {"int",  "float",  "long", "double", "void", "char", "short", "bool"};

const char *preprocessors[] = {"include", "define"};

const char special_symbols[] = {'?', ';', ':', ',', '(',
                                ')', '[', ']', '{', '}'
                               };


int row = 1, col = 1;
FILE *fp;

typedef struct token
{
    int row, col;
    char type[10];
    char lexeme[200];
} *TOKEN;

typedef struct symbol_table_entry
{
    char name[200];
    int size;
    char dtype[20];
} Entry;

typedef struct symbol_table
{
    char name[200];
    Entry entries[100];
    int len_entries;
} Table;

void Program();

void identifier_list();

void identifier_list_prime();

void assign_stat();

void assign_stat_prime();

void declarations();

int is_id_end(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9') || ch == '_')
    {
        return 0;
    }
    return 1;
}

int is_num_end(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return 0;
    }
    return 1;
}

int is_alpha(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        return 1;
    }
    return 0;
}

int is_digit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return 1;
    }
    return 0;
}

int is_delim(char ch)
{
    if (ch == '\n' || ch == ' ' || ch == '\t')
    {
        return 1;
    }
    return 0;
}

int is_dtype(char *str)
{
    for(int i = 0; i < sizeof(dtypes) / sizeof(char *); i++)
    {
        if(strcmp(str, dtypes[i]) == 0)
            return 1;
    }
    return 0;
}

TOKEN createToken(const char *type, const char *lexeme, int col, int row)
{
    TOKEN t = malloc(sizeof(struct token));
    strcpy(t->type, type);
    strcpy(t->lexeme, lexeme);
    t->row = row;
    t->col = col;
    return t;
}

void initTable(Table *t, char *name)
{
    strcpy(t->name, name);
    t->len_entries = 0;
}

void addEntryToTable(Table *t, const char *dtype, char *name, int size)
{
    strcpy(t->entries[t->len_entries].name, name);
    strcpy(t->entries[t->len_entries].dtype, dtype);
    t->entries[t->len_entries].size = size;
    t->len_entries++;
}

void retract(char ch)
{
    if (ch != EOF)
    {
        fseek(fp, -1L, SEEK_CUR);
        col--;
    }
}

void retract_nocheck()
{
    fseek(fp, -1L, SEEK_CUR);
    col--;
}

TOKEN getNextToken()
{
    char buf[1000] = {'\0'};
    int i = 0, len = 0, matched;
    int keywords_len = sizeof(keywords) / sizeof(char *);

    char c = fgetc(fp);
    col++;
    while (is_delim(c) || c == '#' || c == '/')
    {
        while (is_delim(c))
        {
            if (c == '\n')
            {
                col = 1;
                row++;
            }
            else
            {
                col++;
            }
            c = fgetc(fp);
        }
        if (c == '/')
        {
            char next = fgetc(fp);
            if (next == '/')
            {
                while (c != '\n')
                {
                    c = fgetc(fp);
                    col++;
                }
                row++;
                col = 1;
            }
            else if (next == '*')
            {
                do
                {
                    while (c != '*')
                    {
                        c = fgetc(fp);
                        col++;
                        if (c == '\n')
                        {
                            col = 1;
                            row++;
                        }
                    }
                    c = fgetc(fp);
                    col++;
                    if (c == '\n')
                    {
                        col = 1;
                        row++;
                    }
                }
                while (c != '/');
            }
            else
            {
                break;
            }
        }
        if (c == '#')
        {
            c = fgetc(fp);
            col++;

            while (is_alpha(c))
            {
                buf[len++] = c;
                c = fgetc(fp);
                col++;
            }
            buf[len] = '\0';

            matched = 0;
            for (int i = 0; i < sizeof(preprocessors) / sizeof(char *); i++)
            {
                if (strcmp(buf, preprocessors[i]) == 0)
                {
                    matched = 1;
                    break;
                }
            }

            if (matched)
            {
                while (c != '\n')
                {
                    c = fgetc(fp);
                    col++;
                }
            }
            else
            {
                retract(c);
                for (len = len - 1; len > 0; len--)
                {
                    retract_nocheck(fp);
                }
            }
            len = 0;
        }
    }

    while (c != EOF)
    {
        if (is_alpha(c) || c == '_')
        {
            while (c >= 'a' && c <= 'z')
            {
                buf[len++] = c;
                matched = 0;

                for (int i = 0; i < keywords_len; i++)
                {
                    if (len <= strlen(keywords[i]) &&
                            strncmp(buf, keywords[i], len) == 0)
                    {
                        if (len == strlen(keywords[i]))
                        {
                            c = fgetc(fp);
                            retract(c);
                            if (is_id_end(c))
                            {
                                buf[len] = '\0';
                                return createToken("KEYWD", buf, col - strlen(buf), row);
                            }
                        }
                        matched = 1;
                    }
                }
                c = fgetc(fp);
                col++;
                if (!matched)
                {
                    break;
                }
            }

            while (!is_id_end(c))
            {
                buf[len++] = c;
                c = fgetc(fp);
                col++;
            }
            retract(c);

            buf[len] = '\0';
            return createToken("IDENT", buf, col - strlen(buf), row);
        }
        else if (is_digit(c))
        {
            while (is_digit(c))
            {
                buf[len++] = c;
                c = fgetc(fp);
                col++;
            }
            buf[len] = '\0';
            if (c != EOF)
                fseek(fp, -1L, SEEK_CUR);
            return createToken("NUM", buf, col - strlen(buf), row);
        }
        else if (c == '=')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("RELOP", "==", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("ARIOP", "=", col - 1, row); // Assignment operator
            }
        }
        else if (c == '>')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("RELOP", ">=", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("RELOP", ">", col - 1, row);
            }
// PROGRAM 1:
        }
        else if (c == '<')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("RELOP", "<", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("RELOP", "<=", col - 1, row);
            }
        }
        else if (c == '+')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("ARIOP", "+=", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("ARIOP", "+", col - 1, row);
            }
        }
        else if (c == '-')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("ARIOP", "-=", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("ARIOP", "-", col - 1, row);
            }
        }
        else if (c == '*')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("ARIOP", "*=", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("ARIOP", "*", col - 1, row);
            }
        }
        else if (c == '/')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("ARIOP", "/=", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("ARIOP", "/", col - 1, row);
            }
        }
        else if (c == '%')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("ARIOP", "%%=", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("ARIOP", "%%", col - 1, row);
            }
        }
        else if (c == '!')
        {
            c = fgetc(fp);
            if (c == '=')
            {
                col++;
                return createToken("RELOP", "!=", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("LOGOP", "!", col - 1, row);
            }
        }
        else if (c == '&')
        {
            c = fgetc(fp);
            if (c == '&')
            {
                col++;
                return createToken("LOGOP", "&&", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("ARIOP", "&", col - 1, row);
            }
        }
        else if (c == '|')
        {
            c = fgetc(fp);
            if (c == '|')
            {
                col++;
                return createToken("LOGOP", "||", col - 2, row);
            }
            else
            {
                retract(c);
                return createToken("ARIOP", "|", col - 1, row);
            }
        }
        else if (c == '"')
        {
            char prev = c;
            c = fgetc(fp);
            col++;
            while (!(c == '"' && prev != '\\'))
            {
                buf[len++] = c;
                prev = c;
                c = fgetc(fp);
                col++;
            }
            buf[len] = '\0';
            return createToken("STRING", buf, col - strlen(buf) - 2, row);
        }
        else if (c == '\'')
        {
            char prev = c;
            c = fgetc(fp);
            col++;
            while (!(c == '\'' && prev != '\\'))
            {
                buf[len++] = c;
                prev = c;
                c = fgetc(fp);
                col++;
            }
            buf[len] = '\0';
            return createToken("CHAR", buf, col - strlen(buf) - 2, row);
        }
        else
        {
            for (int i = 0; i < sizeof(special_symbols) / sizeof(char); i++)
            {
                if (c == special_symbols[i])
                {
                    buf[0] = special_symbols[i];
                    buf[1] = '\0';
                    return createToken("SPSYM", buf, col - 1, row);
                }
            }
            buf[0] = c;
            buf[1] = '\0';
            return createToken("ERR", buf, col - 1, row);
        }
        c = fgetc(fp);
    }

    return createToken("EOF", "", col, row);
}

void retractToken(TOKEN t)
{
    if(row == t->row)
    {
        fseek(fp, t->col - col, SEEK_CUR);
        col = t->col;
    }
}

int hasLexemeInTable(Table *table, char *lexeme)
{
    for(int i = 0; i < table->len_entries; i++)
    {
        if(strcmp(table->entries[i].name, lexeme) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void printAllTables(Table tables[], int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("\n- - - %s - - -\n", tables[i].name);
        for(int j = 0; j < tables[i].len_entries; j++)
        {
            printf("%s\t %s\t %d\n", tables[i].entries[j].dtype, tables[i].entries[j].name, tables[i].entries[j].size);
        }
    }
}

int sizeof_str(char *str)
{
    if (strcmp(str, "int") == 0)
    {
        return sizeof(int);
    }
    else if (strcmp(str, "short") == 0)
    {
        return sizeof(short);
    }
    else if (strcmp(str, "long") == 0)
    {
        return sizeof(long);
    }
    else if (strcmp(str, "char") == 0)
    {
        return sizeof(char);
    }
    else if (strcmp(str, "bool") == 0)
    {
        return 1;
    }
    else if (strcmp(str, "float") == 0)
    {
        return sizeof(float);
    }
    else if (strcmp(str, "double") == 0)
    {
        return sizeof(double);
    }
    else if (strcmp(str, "void") == 0)
    {
        return 0;
    }
}

void printToken(TOKEN t)
{
    printf("<%s, %s, %d, %d>\n", t->type, t->lexeme, t->row, t->col);
}

void failure(const char *msg, ...)
{
    va_list argptr;
    va_start(argptr, msg);
    fprintf(stderr, "Failed : ");
    vfprintf(stderr, msg, argptr);
    fprintf(stderr, "\n");
    va_end(argptr);
    exit(1);
}

void success()
{
    printf("Sucess!!\n");
}

void assign_stat_prime()
{
    TOKEN t = getNextToken();
    if(strcmp(t->lexeme, "=") == 0)
    {
        free(t);
        t = getNextToken();
        if(strcmp(t->type, "IDENT") == 0)
        {
            free(t);
            t = getNextToken();
            if(strcmp(t->lexeme, ";") == 0)
            {
                return;
            }
            else
            {
                int r = t->row, c = t->col;
                free(t);
                failure("; expected at row: %d, col: %d", r, c);
            }
        }
        else if(strcmp(t->type, "NUM") == 0)
        {
            free(t);
            t = getNextToken();
            if(strcmp(t->lexeme, ";") == 0)
            {
                return;
            }
            else
            {
                int r = t->row, c = t->col;
                free(t);
                failure("; expected at row: %d, col: %d", r, c);
            }
        }
        else
        {
            int r = t->row, c = t->col;
            free(t);
            failure("number or identifier expected at row: %d, col: %d", r, c);
        }
        return;
    }
    else
    {
        int r = t->row, c = t->col;
        free(t);
        failure("= expected at row: %d, col: %d", r, c);
    }
}

void assign_stat()
{
    TOKEN t = getNextToken();
    if(strcmp(t->type, "IDENT") == 0)
    {
        assign_stat_prime();
    }
    else
    {
        int r = t->row, c = t->col;
        free(t);
        failure("Identifier expected at row: %d, col: %d", r, c);
    }
}

void identifier_list_prime()
{
    TOKEN t = getNextToken();
    if(strcmp(t->lexeme, ",") == 0)
    {
        identifier_list();
        return;
    }
    else if(strcmp(t->lexeme, ";") == 0)
    {
        retractToken(t);
        free(t);
        return;
    }
    else
    {
        int r = t->row, c = t->col;
        free(t);
        failure("; expected at row: %d, col: %d", r, c);
    }
}

void identifier_list()
{
    TOKEN t = getNextToken();
    if(strcmp(t->type, "IDENT") == 0)
    {
        identifier_list_prime();
    }
    else
    {
        int r = t->row, c = t->col;
        free(t);
        failure("Identifier expected at row: %d, col: %d", r, c);
    }
}

void declarations()
{
    TOKEN t = getNextToken();
    if(is_dtype(t->lexeme))
    {
        free(t);

        identifier_list();

        t = getNextToken();

        if(strcmp(t->lexeme, ";") == 0)
        {
            free(t);
            declarations();
            return;
        }
        else
        {
            int r = t->row, c = t->col;
            free(t);
            failure("; expected at row: %d, col: %d", r, c);
        }
    }
    else if(strcmp(t->type, "IDENT") == 0)
    {
        retractToken(t);
        free(t);
        return;
    }
    else
    {
        int r = t->row, c = t->col;
        free(t);
        failure("Datatype or identifier expected at row: %d, col: %d", r, c);
    }
}

void Program()
{
    TOKEN t = getNextToken();
    if(strcmp(t->lexeme, "main") == 0)
    {
        free(t);
        t = getNextToken();
        if(strcmp(t->lexeme, "(") == 0)
        {
            free(t);
            t = getNextToken();
            if(strcmp(t->lexeme, ")") == 0)
            {
                free(t);
                t = getNextToken();
                if(strcmp(t->lexeme, "{") == 0)
                {
                    free(t);
                    declarations();
                    assign_stat();
                    t = getNextToken();
                    if(strcmp(t->lexeme, "}") == 0)
                    {
                        free(t);
                        return;
                    }
                    else
                    {
                        int r = t->row, c = t->col;
                        free(t);
                        failure("} expected at row: %d, col: %d", r, c);
                    }
                }
                else
                {
                    int r = t->row, c = t->col;
                    free(t);
                    failure("{ expected at row: %d, col: %d", r, c);
                }
            }
            else
            {
                int r = t->row, c = t->col;
                free(t);
                failure(") expected at row: %d, col: %d", r, c);
            }
        }
        else
        {
            int r = t->row, c = t->col;
            free(t);
            failure("( expected at row: %d, col: %d", r, c);
        }

    }
    else
    {
        int r = t->row, c = t->col;
        free(t);
        failure("main expected at row: %d, col: %d", r, c);
    }
}

int main(int argc, char **argv)
{
    TOKEN t;
    if (argc != 2)
    {
        printf("Usage: ./ex1 <src file path>\n");
        return 1;
    }
    else
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            printf("Couldn't open source file\n");
            return 1;
        }

        Program();

        t = getNextToken();
        if(strcmp(t->type, "EOF") == 0)
        {
            success();
        }
        else
        {
            int r = t->row, c = t->col;
            free(t);
            failure("Program should end at row: %d, col: %d", r, c);
        }
    }
}