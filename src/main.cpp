
#include "main.h"

static opt_info_t opt;

static void cwhelp(opt_info_t *oit);

static handle_func_t handlers[] = 
{
	{"tool_path", tool_getpath},
	{"gen_pth", gen_thread_code},
	{"gen_C", gen_C},
	{"gen_Cpp", gen_Cpp},
	{"gen_project", gen_project},
	{"help", cwhelp},
};


/*初始化默认参数*/
static void opt_init(int argc, char **argv)
{
	int ch;
	int ierr = 0;

	opt.argc = 0;
	/*获取当前工作路径*/
	if(getcwd(opt.pwd_path, BUF_LEN_256B) == NULL)
	{
		LOG_ERROR("Failed to obtain the current working path! [ getcwd() error]");
		exit(-1);
	}

	// printf("%s\n", opt.pwd_path);
	
	if(argc > 1)
	{
		if(strcmp(argv[1], "pth") == 0)
		{
			opt.argc = 1;
			strncpy(opt.exec_name, "gen_pth", BUF_LEN_ARG2);
			strncpy(opt.argv[0], "pth", BUF_LEN_ARG2);
			strncpy(opt.argv_[0], "thread_api", BUF_LEN_ARG2);           /*默认文件名*/
			return;
		}
		else if(strcmp(argv[1], "path") == 0)
		{
			opt.argc = 1;
			
			strncpy(opt.exec_name, "tool_path", BUF_LEN_ARG2);
			strncpy(opt.argv[0], "path", BUF_LEN_ARG2);
			strncpy(opt.argv_[0], "get_path", BUF_LEN_ARG2);           /*默认文件名*/
			if (argc > 2)
			{
				strncpy(opt.argv_[opt.argc], argv[2], BUF_LEN_ARG2);
				opt.argc++;
			}
			return;
		}
	}

	while ((ch = getopt(argc, argv, "p:c:n:hH")) != -1) 
	{
		switch(ch) 
		{
		case 'c':
		{
			if(ierr == 1)
			{
				LOG_ERROR("- n and - c can only specify one.");
				exit(-1);
			}
			ierr = 1;
			if (opt.argc == 0)
			{
				strncpy(opt.exec_name, "gen_C", BUF_LEN_ARG2);
			}
			strncpy(opt.argv[opt.argc], "c", BUF_LEN_ARG2);
			string s1 = optarg;
			tihuan_(s1);
			strncpy(opt.argv_[opt.argc], s1.data(), BUF_LEN_ARG2);           /*默认文件名*/
			opt.argc++;
			break;
		}
		case 'n':
		{
			if(ierr == 1)
			{
				LOG_ERROR("- n and - c can only specify one.");
				exit(-1);
			}
			ierr = 1;
			if (opt.argc == 0)
			{
				strncpy(opt.exec_name, "gen_Cpp", BUF_LEN_ARG2);
			}
			strncpy(opt.argv[opt.argc], "n", BUF_LEN_ARG2);
			string s1 = optarg;
			tihuan_(s1);
			strncpy(opt.argv_[opt.argc], s1.data(), BUF_LEN_ARG2);		/*默认文件名*/
			opt.argc++;
			break;
		}
		case 'p':
		{
			strncpy(opt.exec_name, "gen_project", BUF_LEN_ARG2);
			strncpy(opt.argv[opt.argc], "p", BUF_LEN_ARG2);
			strncpy(opt.argv_[opt.argc], optarg, BUF_LEN_ARG2);
			opt.argc++;
			break;
		}
		case 'H':
		case 'h':
		{
			strncpy(opt.exec_name, "help", BUF_LEN_ARG2);
			return;
		}
		default:
			printf("Command usage error.\nPlease enter cw-widget-cpp -h (or -H)\n");
			exit(-1);
		break;
		}
	}
	
	if (opt.argc == 0)
	{
		printf("Command usage error.\nPlease enter cw-widget-cpp -h (or -H)\n");
		exit(-1);
	}
	
}

static void cwhelp(opt_info_t *oit)
{
	cout << "cw-widget-cpp("<< CW_WIDGET_CPP_VERSION <<") parameter Description:\n"
			"-c: Generate C language. h and. c files, using this parameter followed by the name of the file to be generated\n"
			"	for example: cw-widget-cpp -c ctest\n"
			"-n: Generate .h and .cpp files, using this parameter followed by the name of the file to be generated\n"
			"	for example: cw-widget-cpp -n cpptest\n"
			"-p: Generate a project, using this parameter followed by the name of the project to be generated\n"
			"	for example: cw-widget-cpp -p testproject or cw-widget-cpp -p testproject -c ctest\n"
			"pth: API for generating Linux C threads\n"
			"	for example: cw-widget-cpp pth\n"
			"path: Obtain the absolute path of the '.h .c .cpp' file under the current working path\n"
			"	for example: cw-widget-cpp pth\n";
	exit(-1);
}

static void run()
{
	for (size_t i = 0; i < ARRAY_SIZE(handlers); i++)
	{
		if (strcmp(handlers[i].func_name, opt.exec_name) == 0)
		{
			if (handlers[i].exec != NULL)
			{
				handlers[i].exec(&opt);
				break;
			}
		}
	}
}


int main(int argc, char **argv)
{
	log_attribute_set(NULL, 0, 0, 0);
	opt_init(argc, argv);
	run();
	return 0;
}

