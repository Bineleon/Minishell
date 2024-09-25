
Nelbi Léon <nelbi.leon@gmail.com>
16:31 (il y a 5 heures)
À moi

/* ╔════════════════════════════════════╗ */
/* ║        ENUM ET STRUCTURES          ║ */
/* ╚════════════════════════════════════╝ */

typedef enum e_token
{
WORD = -1,
PIPE = '|',
IN = '<',
OUT = '>',
EXPAND = '$',
SQUOTE = '\'',
DQUOTE = '\"',
SPC = ' ',
TRUNC = 1,
APPEND = 2,
HEREDOC = 3,
CMD = 4,
ARG = 5
} t_token;

typedef enum e_mem
{
MALLOC,
FREE,
FULL_CLEAN
} t_mem;

typedef enum e_bool
{
false,
true
} t_bool;

typedef struct s_cmd
{
char **args;
char *input;
char *output;
int infile;
int outfile;
t_bool skip_cmd;
struct s_cmd *next;
} t_cmd;

typedef struct s_garbage_co
{
void        *ptr;
struct s_garbage_co *next;
} t_garbage_co;

typedef struct s_data
{
char  **envp_cpy;
size_t cmds_count;
int  fd[2];
t_cmd      *cmds;
t_token         *token;
t_garbage_co  *garbage;
int             exit_code;
t_list      *env;   // Représente l'environnement (liste chaînée de variables)
} t_data;

/* ╔════════════════════════════════════╗ */
/* ║       Fonction de gestion GC       ║ */
/* ╚════════════════════════════════════╝ */

static void *gc_free(t_garbage_co *garbage, void *ptr)
{
while (garbage)
{
if (garbage->ptr == ptr)
{
free(garbage->ptr);
garbage->ptr = NULL;
}
garbage = garbage->next;
}
return (NULL);
}

static void *gc_full_clean(t_garbage_co *garbage)
{
t_garbage_co *tmp;

tmp = garbage;
while (garbage->next)
{
tmp = garbage;
free(tmp->ptr);
garbage = garbage->next;
free(tmp);
}
free(garbage->ptr);
free(garbage);
return (NULL);
}

static void *gc_malloc(t_data *data, size_t size, void *ptr)
{
t_garbage_co *new;

new = malloc(sizeof(t_garbage_co));
if (!new)
return (perror("malloc"), gc_mem(FULL_CLEAN, 0, NULL), exit(EXIT_FAILURE), NULL);
if (ptr)
new->ptr = ptr;
else
new->ptr = malloc(size);
if (!new->ptr)
return (perror("malloc"), gc_mem(FULL_CLEAN, 0, NULL), exit(EXIT_FAILURE), NULL);
if (data->garbage)
{
new->next = data->garbage;
data->garbage = new;
}
else if (data->garbage == NULL)
{
new->next = NULL;
data->garbage = new;
}
return (new->ptr);
}

void *gc_mem(t_mem type, size_t size, void *ptr)
{
t_data *data;
t_garbage_co *garb;

data = get_data();
garb = data->garbage;
if (type == MALLOC)
return (gc_malloc(data, size, ptr));
else if (type == FULL_CLEAN && garb)
return (gc_full_clean(garb));
else if (type == FREE && garb)
return (gc_free(garb, ptr));
return (NULL);
}

/* ╔════════════════════════════════════╗ */
/* ║     Gestion des variables $ENV     ║ */
/* ╚════════════════════════════════════╝ */

char *get_elem_env(t_list *env, char *key)
{
t_list *tmp;
int len;
int t;

if (!key)
return (NULL);
tmp = env;
len = len_list(tmp);
t = ft_strlen(key);
while (len--)
{
if (ft_strncmp(tmp->str, key, t) == 0)
{
len = 0;
while (tmp->str[len])
if (tmp->str[len++] == '=')
break ;
return (ft_strdup(&(tmp->str[len])));
}
tmp = tmp->next;
}
return (NULL);
}

/* ╔════════════════════════════════════╗ */
/* ║  Gestion des variables dans les "" ║ */
/* ╚════════════════════════════════════╝ */

static char *expand_variable(char *line, int *i, t_data *data)
{
int var_len = 0;
char *var_name;
char *var_value;

(*i)++;  // Sauter le '$'
while (line[*i + var_len] && (ft_isalnum(line[*i + var_len]) || line[*i + var_len] == '_'))
var_len++;

var_name = gc_mem(MALLOC, sizeof(char) * (var_len + 1), NULL);
ft_strncpy(var_name, &line[*i], var_len);
var_name[var_len] = '\0';

var_value = get_elem_env(data->env, var_name);
if (!var_value)
var_value = ft_strdup("");  // Si la variable n'existe pas, utiliser une chaîne vide

(*i) += var_len - 1;  // Mettre à jour l'index pour sauter la variable

return var_value;
}

static char *handle_double_quotes(char *line, int *i, t_data *data)
{
char *str = gc_mem(MALLOC, sizeof(char) * ft_strlen(line), NULL);
int j = 0;

(*i)++;  // Sauter la double quote ouvrante
while (line[*i] && line[*i] != '"')
{
if (line[*i] == '$')  // Si on trouve une variable à expanser
{
char *var_value = expand_variable(line, i, data);
while (*var_value)
str[j++] = *var_value++;
}
else
{
str[j++] = line[*i];
}
(*i)++;
}
str[j] = '\0';
if (line[*i] == '"')
(*i)++;  // Sauter la quote fermante
return str;
}

/* ╔════════════════════════════════════╗ */
/* ║     Gestion des quotes et tokens   ║ */
/* ╚════════════════════════════════════╝ */

static int skip_quotes(char *line, int i, char quote)
{
i++; // Sauter la quote initiale
while (line[i] && line[i] != quote)
i++;
return i;
}

static int is_separator(char c)
{
return (c == '|' || c == '<' || c == '>' || c == '$');
}

static t_token get_token_type(char c)
{
if (c == '|')
return PIPE;
if (c == '<')
return IN;
if (c == '>')
return OUT;
if (c == '$')
return EXPAND;
return WORD;
}

t_token *parse_command(char *line, t_data *data)
{
t_token *tokens;
int i = 0;
int j = 0;

tokens = gc_mem(MALLOC, sizeof(t_token) * ft_strlen(line) + 1, NULL);
if (!tokens)
return NULL;

while (line[i])
{
if (line[i] == '"')
{
tokens[j] = WORD;
handle_double_quotes(line, &i, data);  // Gérer les double quotes avec expansion des variables
}
else if (line[i] == '\'')
{
// Ignorer les variables dans les simples quotes
tokens[j] = WORD;
i = skip_quotes(line, i, '\'');
}
else if (is_separator(line[i]))
{
tokens[j] = get_token_type(line[i]);
}
else
{
tokens[j] = WORD;
}
j++;
i++;
}
tokens[j] = 0;
return tokens;
}

/* ╔════════════════════════════════════╗ */
/* ║     Extraction et nettoyage args   ║ */
/* ╚════════════════════════════════════╝ */

static char *remove_quotes(char *str)
{
char *new_str;
int i = 0;
int j = 0;

new_str = gc_mem(MALLOC, sizeof(char) * (ft_strlen(str) + 1), NULL);
if (!new_str)
return NULL;

while (str[i])
{
if (str[i] == '\'' || str[i] == '"')
{
char quote = str[i];
i++; // Sauter la quote initiale
while (str[i] && str[i] != quote)
new_str[j++] = str[i++];
if (str[i] == quote) // Sauter la quote fermante
i++;
}
else
new_str[j++] = str[i++];
}
new_str[j] = '\0';
return new_str;
}

/* ╔════════════════════════════════════╗ */
/* ║   Création de la commande finale   ║ */
/* ╚════════════════════════════════════╝ */

t_cmd *create_command(t_token *tokens, char **args, t_data *data)
{
t_cmd *cmd;
int i = 0;
int arg_index = 0;

cmd = gc_mem(MALLOC, sizeof(t_cmd), NULL);
if (!cmd)
return NULL;

cmd->args = gc_mem(MALLOC, sizeof(char *) * (count_args(tokens) + 1), NULL);
if (!cmd->args)
return NULL;

while (tokens[i] && tokens[i] != PIPE)
{
if (tokens[i] == WORD)
{
// On enlève les quotes et expanse les variables si nécessaire
cmd->args[arg_index++] = remove_quotes(args[i]);
}
i++;
}
cmd->args[arg_index] = NULL;

// Gérer les redirections pour cette commande
manage_redirections(cmd, tokens, args);

return cmd;
}

/* ╔════════════════════════════════════╗ */
/* ║      Fonction principale revue     ║ */
/* ╚════════════════════════════════════╝ */

bool parseline(t_data *data, char *line)
{
t_token *tokens;
t_cmd *cmd;
char **args = split_args(line); // Fonction fictive pour diviser la ligne en arguments

tokens = parse_command(line, data);
if (!tokens)
return false;

// Vérifier les erreurs de syntaxe avant d'aller plus loin
if (!check_errors(tokens))
{
gc_mem(FREE, 0, tokens);
return false;
}

// Créer la commande et gérer les redirections
cmd = create_command(tokens, args, data);
if (!cmd)
{
gc_mem(FREE, 0, tokens);
return false;
}

// Ajouter la commande à la liste des commandes du shell
data->cmds = cmd;

gc_mem(FREE, 0, tokens); // Libérer les tokens une fois qu'ils sont traités
return true;
}