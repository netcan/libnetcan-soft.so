#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <netcan-soft.h>


char *fcs(char *title, char *path, int cs, char *fc, int fcsize)
{
    mkdir("/mnt/UsrDisk/NetCan-Soft");
    mkdir("/mnt/UsrDisk/NetCan-Soft/Settings");
    FILE *themeconf;
    FILE *default_theme;
    if ((default_theme =
	 fopen("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_default_theme.conf",
	       "r")) == NULL) {
	default_theme =
	    fopen
	    ("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_default_theme.conf",
	     "w");
	fputs("Default_Theme = 1\n", default_theme);
	fclose(default_theme);
	default_theme =
	    fopen
	    ("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_default_theme.conf",
	     "r");
    }


    if ((themeconf =
	 fopen("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_theme.conf",
	       "r")) == NULL) {
	themeconf =
	    fopen("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_theme.conf", "w");
	fputs("[FileChooce_theme]\n", themeconf);
	fputs("# Copyright NetCan-Soft 2012\n", themeconf);
	fputs
	    ("# QQ:1469709759\n# Report bugs to <1469709759@qq.com> (in Chinese or English)\n",
	     themeconf);
	fputs("# More: http://ncan.ys168.com\n", themeconf);
	fputs("# 注释请用 \'#\'\n", themeconf);
	fputs("# 主题名请小于8个字符(4个汉字)\n", themeconf);
	fputs("Theme_Name = 自定义\nTheme_Author = NetCan\n", themeconf);
	fputs("[KeyBoard]\n", themeconf);
	fputs("# 值取键值\n", themeconf);
	fputs
	    ("UP = 171\nDOWN = 172\nLEFT = 174\nRIGHT = 173\nMENU = 27\nENTER = 13\n",
	     themeconf);
	fputs("[Theme_Set]\n", themeconf);
	fputs("# 值取颜色值,具体请看Bash转义\n", themeconf);
	fputs
	    ("Box = 44\nCursor = 43\nTitle = 36\nPath = 31\nMenu_Fix_Color = 42\nSelect = 35\n",
	     themeconf);
	fclose(themeconf);
	themeconf =
	    fopen("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_theme.conf", "r");

    }






    if (chdir(path) != 0)
	return 0;

    DIR *dp;
    dp = opendir(".");

    int draw, n = 0, total = -1;
    if (total == -1) {
	total = ftotal(dp);
	closedir(dp);
    }


    char files[total][256];
    struct dirent **fd;
    for (draw = 0; draw < total; draw++)
	for (n = 0; n < 256; n++) {
	    files[draw][n] = 0;
	}
    for (n = 0; n < total; n++)
	files[n][255] = 7;

    scandir(".", &fd, 0, alphasort);


    for (draw = 0, n = 1; n <= total; n++) {
	if (fd[n]->d_type == 4) {
	    memcpy(files[draw], fd[n]->d_name, strlen(fd[n]->d_name));
	    files[draw][255] = 4;
	    draw++;
	}
    }

    for (n = 1; n <= total; n++) {
	if (fd[n]->d_type != 4) {
	    memcpy(files[draw], fd[n]->d_name, strlen(fd[n]->d_name));

	    if (fd[n]->d_type == 8)
		files[draw][255] = 2;
	    if (fd[n]->d_type == 10)
		files[draw][255] = 6;
	    if (fd[n]->d_type == 2 || fd[n]->d_type == 6)
		files[draw][255] = 5;
	    draw++;
	}
    }








// draw windows
    int key;
    int chooce = 1;
    int theme;
    fscanf(default_theme, "Default_Theme = %d\n", &theme);
    if (theme <= 0 || theme > 3)
	theme = 2;
    fclose(default_theme);



// Setting Theme
    char author[512];
    memset(author, 0, sizeof(author));

    struct fcs_theme purple;
    struct fcs_theme green;
    struct fcs_theme self;
    struct fcs_theme usetheme;

// Purple
    purple.up = 171;
    purple.down = 172;
    purple.left = 174;
    purple.right = 173;
    purple.enter = 13;
    purple.menu = 27;
    purple.fix = 33;
    purple.box = 45;
    purple.cursor = 41;
    purple.title = 33;
    purple.menu_color = 46;
    purple.menu_font_color = 37;
    purple.path = 34;

// Green
    green.up = 171;
    green.down = 172;
    green.left = 174;
    green.right = 173;
    green.enter = 13;
    green.menu = 27;
    green.fix = 31;
    green.menu_color = 41;
    green.menu_font_color = 37;
    green.box = 46;
    green.cursor = 45;
    green.title = 32;
    green.path = 33;

// Self
    int l = fline(themeconf);
    char null[512];
    char themename[200];
    memset(themename, 0, sizeof(themename));
    for (n = 0; n <= l; n++) {
	memset(null, 0, sizeof(null));
	fgets(null, sizeof(null), themeconf);
	sscanf(null, "UP = %d", &self.up);
	sscanf(null, "DOWN = %d", &self.down);
	sscanf(null, "LEFT = %d", &self.left);
	sscanf(null, "RIGHT = %d", &self.right);
	sscanf(null, "MENU = %d", &self.menu);
	sscanf(null, "ENTER = %d", &self.enter);

	sscanf(null, "Box = %d", &self.box);
	sscanf(null, "Cursor = %d", &self.cursor);
	sscanf(null, "Title = %d", &self.title);
	sscanf(null, "Path = %d", &self.path);
	sscanf(null, "Menu_Fix_Color = %d", &self.menu_color);
	sscanf(null, "Select = %d", &self.fix);
	sscanf(null, "Theme_Name = %s", themename);
	sscanf(null, "Theme_Author = %s", author);
    }


    for (n = 0; n <= l; n++) {
	memset(null, 0, sizeof(null));
	fgets(null, sizeof(null), themeconf);
	sscanf(null, "Theme_Name = %s", themename);
    }

    fclose(themeconf);
    memset(null, 0, sizeof(null));
    self.menu_font_color = 37;

    char menu[20][20] =
	{ "  单选  ", "  多选  ", "选定目录", "  帮助  ", "  确定  ",
	"  返回  ", " Theme  ", "  梦幻  ", "  靛青  "
    };
    l = (int) (8 - strlen(themename)) / 2;
    sprintf(menu[9] + l, "%s", themename);

    for (n = 0; n < 8; n++)
	if (menu[9][n] == 0)
	    menu[9][n] = ' ';


    for (n = 0; n < 20; n++)
	for (draw = strlen(menu[n]); draw < 20; draw++)
	    menu[n][draw] = 0;



    char mode[3][5];
    for (draw = 0; draw < 3; draw++)
	for (n = 0; n < 5; n++)
	    mode[draw][n] = 0;



    char msg[200];
    for (draw = 0; draw < 200; draw++)
	msg[draw] = 0;

    char pwd[512];
    getcwd(pwd, sizeof(pwd));
    int page, np = 1;
    int select = 0;

    n = 0;
    if (total % 10 == 0)
	page = total / 10;
    else
	page = total / 10 + 1;

    int line = 0;

    if (theme == 1)
	usetheme = purple;
    if (theme == 2)
	usetheme = green;
    if (theme == 3)
	usetheme = self;




    for (draw = 0; draw < 3; draw++)
	mode[draw][0] = usetheme.box - 40;
    mode[0][0] = usetheme.menu_color - 40;

    for (n = 0; n < 20; n++)
	menu[n][19] = 0;
    menu[6][19] = usetheme.box - 40;

    if (cs != 1 && cs != 2)
	cs = 2;

    if (cs == 1)
	chooce = 0;
    if (cs == 2)
	chooce = 1;

    sprintf(msg, "已标记: %d    Page: %d/%d    line: %d/%d", select, np,
	    page, line + (np - 1) * 10 + 1, total);
    int tmp;

    for (n = 0; n < fcsize; n++)
	fc[n] = 0;

    printf("\e[?25l");

    while (1) {
	printf("\n\n\n\n\n\n");


	files[(np - 1) * 10 + line][250] = usetheme.cursor - 40;
	menu[chooce][19] = usetheme.cursor - 40;
	menu[theme + 6][19] = usetheme.cursor - 40;
	printf(" \e[%d;1m|\e[%d;%d;1mNetCan-Soft%35s\e[37m|\e[0m\n",
	       usetheme.box, usetheme.box, usetheme.title, title);
	if (strlen(pwd) > 39)
	    printf
		(" \e[%d;1m[\e[0m\e[%d;1mPath\e[0m: %.39s>\e[%d;1m]\e[0m\n",
		 usetheme.box, usetheme.path, pwd, usetheme.box);
	else
	    printf
		(" \e[%d;1m[\e[0m\e[%d;1mPath\e[0m: %-40s\e[%d;1m]\e[0m\n",
		 usetheme.box, usetheme.path, pwd, usetheme.box);
	printf
	    (" \e[%d;1m|\e[%d;%d;1m            Filename                 \e[0m\e[%d;1m|\e[0m\e[%d;%d;1m  Menu  \e[%d;37;1m|\e[0m\n",
	     usetheme.box, usetheme.menu_font_color, (int) mode[0][0] + 40,
	     usetheme.box, usetheme.menu_font_color, (int) mode[1][0] + 40,
	     usetheme.box);


	for (draw = 4; draw < 14; draw++) {
	    if (total - np * 10 >= 0) {
		if (files[draw - 4 + (np - 1) * 10][253] != '\241'
		    && files[draw - 4 + (np - 1) * 10][254] != '\314') {
		    if (strlen(files[draw - 4 + (np - 1) * 10]) > 33)
			printf
			    (" \e[%d;1m|\e[0m\e[0m\e[%d;%d;1m%.34s...\e[0m\e[%d;1m|\e[0m\e[%d;0m%s\e[%d;1m|\e[0m\e[0m\n",
			     usetheme.box,
			     (int) files[draw - 4 + (np - 1) * 10][250] +
			     40,
			     (int) files[draw - 4 + (np - 1) * 10][255] +
			     30, files[draw - 4 + (np - 1) * 10],
			     usetheme.box, (int) menu[draw - 4][19] + 40,
			     menu[draw - 4], usetheme.box);
		    else
			printf
			    (" \e[%d;1m|\e[0m\e[0m\e[%d;%d;1m%-37s\e[0m\e[%d;1m|\e[0m\e[%d;1m%s\e[%d;1m|\e[0m\n",
			     usetheme.box,
			     (int) files[draw - 4 + (np - 1) * 10][250] +
			     40,
			     (int) files[draw - 4 + (np - 1) * 10][255] +
			     30, files[draw - 4 + (np - 1) * 10],
			     usetheme.box, (int) menu[draw - 4][19] + 40,
			     menu[draw - 4], usetheme.box);
		} else {
		    if (strlen(files[draw - 4 + (np - 1) * 10]) > 33)
			printf
			    (" \e[%d;1m|\e[0m\e[%d;%d;1m%c%c\e[0m\e[%d;%d;1m%.32s...\e[0m\e[%d;1m|\e[0m\e[%d;0m%s\e[%d;1m|\e[0m\e[0m\n",
			     usetheme.box, usetheme.fix,
			     (int) files[draw - 4 + (np - 1) * 10][250] +
			     40, files[draw - 4 + (np - 1) * 10][253],
			     files[draw - 4 + (np - 1) * 10][254],
			     (int) files[draw - 4 + (np - 1) * 10][250] +
			     40,
			     (int) files[draw - 4 + (np - 1) * 10][255] +
			     30, files[draw - 4 + (np - 1) * 10],
			     usetheme.box, (int) menu[draw - 4][19] + 40,
			     menu[draw - 4], usetheme.box);
		    else
			printf
			    (" \e[%d;1m|\e[0m\e[%d;%d;1m%c%c\e[0m\e[%d;%d;1m%-35s\e[0m\e[%d;1m|\e[0m\e[%d;1m%s\e[%d;1m|\e[0m\n",
			     usetheme.box, usetheme.fix,
			     (int) files[draw - 4 + (np - 1) * 10][250] +
			     40, files[draw - 4 + (np - 1) * 10][253],
			     files[draw - 4 + (np - 1) * 10][254],
			     (int) files[draw - 4 + (np - 1) * 10][250] +
			     40,
			     (int) files[draw - 4 + (np - 1) * 10][255] +
			     30, files[draw - 4 + (np - 1) * 10],
			     usetheme.box, (int) menu[draw - 4][19] + 40,
			     menu[draw - 4], usetheme.box);
		}


	    } else {
		if (draw - 4 < (10 + total - np * 10)) {
		    if (files[draw - 4 + (np - 1) * 10][253] != '\241'
			&& files[draw - 4 + (np - 1) * 10][254] !=
			'\314') {
			if (strlen(files[draw - 4 + (np - 1) * 10]) > 30)
			    printf
				(" \e[%d;1m|\e[0m\e[0m\e[%d;%d;1m%.34s...\e[0m\e[%d;1m|\e[0m\e[%d;1m%s\e[%d;1m|\e[0m\n",
				 usetheme.box,
				 (int) files[draw - 4 +
					     (np - 1) * 10][250] + 40,
				 (int) files[draw - 4 +
					     (np - 1) * 10][255] + 30,
				 files[draw - 4 + (np - 1) * 10],
				 usetheme.box,
				 (int) menu[draw - 4][19] + 40,
				 menu[draw - 4], usetheme.box);
			else
			    printf
				(" \e[%d;1m|\e[0m\e[0m\e[%d;%d;1m%-37s\e[0m\e[%d;1m|\e[0m\e[%d;1m%s\e[%d;1m|\e[0m\n",
				 usetheme.box,
				 (int) files[draw - 4 +
					     (np - 1) * 10][250] + 40,
				 (int) files[draw - 4 +
					     (np - 1) * 10][255] + 30,
				 files[draw - 4 + (np - 1) * 10],
				 usetheme.box,
				 (int) menu[draw - 4][19] + 40,
				 menu[draw - 4], usetheme.box);
		    } else {
			if (strlen(files[draw - 4 + (np - 1) * 10]) > 30)
			    printf
				(" \e[%d;1m|\e[0m\e[%d;%d;1m%c%c\e[0m\e[%d;%d;1m%.32s...\e[0m\e[%d;1m|\e[0m\e[%d;1m%s\e[%d;1m|\e[0m\n",
				 usetheme.box, usetheme.fix,
				 (int) files[draw - 4 +
					     (np - 1) * 10][250] + 40,
				 files[draw - 4 + (np - 1) * 10][253],
				 files[(np - 1) * 10 + draw - 4][254],
				 (int) files[draw - 4 +
					     (np - 1) * 10][250] + 40,
				 (int) files[draw - 4 +
					     (np - 1) * 10][255] + 30,
				 files[draw - 4 + (np - 1) * 10],
				 usetheme.box,
				 (int) menu[draw - 4][19] + 40,
				 menu[draw - 4], usetheme.box);
			else
			    printf
				(" \e[%d;1m|\e[0m\e[%d;%d;1m%c%c\e[0m\e[%d;%d;1m%-35s\e[0m\e[%d;1m|\e[0m\e[%d;1m%s\e[%d;1m|\e[0m\n",
				 usetheme.box, usetheme.fix,
				 (int) files[draw - 4 +
					     (np - 1) * 10][250] + 40,
				 files[draw - 4 + (np - 1) * 10][253],
				 files[(np - 1) * 10 + draw - 4][254],
				 (int) files[draw - 4 +
					     (np - 1) * 10][250] + 40,
				 (int) files[draw - 4 +
					     (np - 1) * 10][255] + 30,
				 files[draw - 4 + (np - 1) * 10],
				 usetheme.box,
				 (int) menu[draw - 4][19] + 40,
				 menu[draw - 4], usetheme.box);
		    }

		}
		if (draw - 4 >= (10 + total - np * 10))
		    printf
			(" \e[%d;1m|\e[0m                                     \e[%d;1m|\e[0m\e[%d;1m%s\e[%d;1m|\e[0m\n",
			 usetheme.box, usetheme.box,
			 (int) menu[draw - 4][19] + 40, menu[draw - 4],
			 usetheme.box);
	    }
	}
	printf(" \e[%d;1m|%-46.46s|\e[0m\n", usetheme.box, msg);



//mode

	if (mode[0][0] == usetheme.menu_color - 40) {
	    key = getch();

//kill
	    if (key == KILL) {
		printf("\e[?25h");
		default_theme =
		    fopen
		    ("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_default_theme.conf",
		     "w");
		fprintf(default_theme, "Default_Theme = %d\n", theme);
		fclose(default_theme);
		return "KILL";
	    }
// end kill
//down
	    if (key == usetheme.down) {
		if (line < 9) {
		    if (total - 10 * np > 0) {
			line++;
			files[(np - 1) * 10 + line - 1][250] = 0;
		    } else {
			if (line < 9 + total - 10 * np) {
			    line++;
			    files[(np - 1) * 10 + line - 1][250] = 0;
			}
		    }

		} else {
		    if (np < page) {
			files[(np - 1) * 10 + line - 1][250] = 0;
			line = 0;
			np++;
			files[(np - 1) * 10 + line - 1][250] = 0;
		    }

		}
		sprintf(msg, "已标记: %d    Page: %d/%d    line: %d/%d",
			select, np, page, line + (np - 1) * 10 + 1, total);
	    }
//end down
//up
	    if (key == usetheme.up) {
		if (line > 0) {
		    line--;
		    files[(np - 1) * 10 + line + 1][250] = 0;
		} else {
		    if (np > 1) {
			line = 9;
			np--;
			files[(np - 1) * 10 + line + 1][250] = 0;
		    }

		}
		sprintf(msg, "已标记: %d    Page: %d/%d    line: %d/%d",
			select, np, page, line + (np - 1) * 10 + 1, total);

	    }
//end up
//left
	    if (key == usetheme.left) {
		if (np > 1 && np <= page) {
		    files[(np - 1) * 10 + line][250] = 0;
		    np--;
		}
		sprintf(msg, "已标记: %d    Page: %d/%d    line: %d/%d",
			select, np, page, line + (np - 1) * 10 + 1, total);
	    }
//end left
//right
	    if (key == usetheme.right) {
		if (np < page) {
		    if (line + np * 10 < total) {
			files[(np - 1) * 10 + line][250] = 0;
			np++;
		    } else {
			files[(np - 1) * 10 + line][250] = 0;
			np++;
			line = 9 - (np * 10 - total);
		    }
		}


		sprintf(msg, "已标记: %d    Page: %d/%d    line: %d/%d",
			select, np, page, line + (np - 1) * 10 + 1, total);
	    }
//end right
//enter
	    if (key == usetheme.enter) {
		if ((int) files[(np - 1) * 10 + line][255] != 4) {

		    if (chooce == 1) {
			if (files[(np - 1) * 10 + line][253] == 0
			    && files[(np - 1) * 10 + line][254] == 0) {
			    files[(np - 1) * 10 + line][253] = '\241';
			    files[(np - 1) * 10 + line][254] = '\314';
			    select++;
			} else {
			    files[(np - 1) * 10 + line][253] = 0;
			    files[(np - 1) * 10 + line][254] = 0;
			    select--;
			}
		    }

		    if (chooce == 0) {



			if (select == 1) {
			    for (n = 0; n < total; n++) {
				files[n][253] = 0;
				files[n][254] = 0;
				select = 0;
			    }
			    files[(np - 1) * 10 + line][253] = '\241';
			    files[(np - 1) * 10 + line][254] = '\314';
			    select++;
			}



			if (select == 0) {
			    files[(np - 1) * 10 + line][253] = '\241';
			    files[(np - 1) * 10 + line][254] = '\314';
			    select++;
			}




		    }

		}
		if ((int) files[(np - 1) * 10 + line][255] == 4) {
		    printf("\e[?25h");
		    return fcs(title, files[(np - 1) * 10 + line],
			       chooce + 1, fc, fcsize);
		    _exit(0);
		}
		sprintf(msg, "已标记: %d    Page: %d/%d    line: %d/%d",
			select, np, page, line + (np - 1) * 10 + 1, total);

	    }
//end enter
//menu
	    if (key == usetheme.menu) {
		mode[0][0] = usetheme.box - 40;
		mode[1][0] = usetheme.menu_color - 40;

		continue;
	    }
// end menu
	}

	if (mode[1][0] == usetheme.menu_color - 40) {
	    key = getch();
// kill
	    if (key == KILL) {
		printf("\e[?25h");
		default_theme =
		    fopen
		    ("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_default_theme.conf",
		     "w");
		fprintf(default_theme, "Default_Theme = %d\n", theme);
		fclose(default_theme);
		return "KILL";
	    }
// end kill
// down
	    if (key == usetheme.down) {
		if (chooce < 5) {
		    menu[chooce][19] = 0;
		    chooce++;
		} else {
		    menu[chooce][19] = 0;
		    chooce = 0;
		}
		if (chooce == 0)
		    sprintf(msg, "只选择一个文件。", NULL);
		if (chooce == 1)
		    sprintf(msg, "可以选择多个文件。", NULL);
		if (chooce == 2)
		    sprintf(msg, "选择当前目录。", NULL);
		if (chooce == 3)
		    sprintf(msg, "查看帮助。", NULL);
		if (chooce == 4)
		    sprintf(msg, "确定选择。", NULL);
		if (chooce == 5)
		    sprintf(msg, "退出程序。", NULL);



	    }
// end down
// up
	    if (key == usetheme.up) {
		if (chooce > 0) {
		    menu[chooce][19] = 0;
		    chooce--;
		} else {
		    menu[chooce][19] = 0;
		    chooce = 5;
		}
		if (chooce == 0)
		    sprintf(msg, "只选择一个文件。", NULL);
		if (chooce == 1)
		    sprintf(msg, "可以选择多个文件。", NULL);
		if (chooce == 2)
		    sprintf(msg, "选择当前目录。", NULL);
		if (chooce == 3)
		    sprintf(msg, "查看帮助。", NULL);
		if (chooce == 4)
		    sprintf(msg, "确定选择。", NULL);
		if (chooce == 5)
		    sprintf(msg, "退出程序。", NULL);

	    }
//end up
	    if (key == usetheme.enter) {
		if (chooce == 0) {
		    for (n = 0; n < total; n++) {
			files[n][253] = 0;
			files[n][254] = 0;
			select = 0;
			mode[1][0] = usetheme.box - 40;
			mode[0][0] = usetheme.menu_color - 40;
			continue;
		    }
		}
		if (chooce == 0 || chooce == 1) {
		    sprintf(msg,
			    "已标记: %d    Page: %d/%d    line: %d/%d",
			    select, np, page, line + (np - 1) * 10 + 1,
			    total);
		    mode[1][0] = usetheme.box - 40;
		    mode[0][0] = usetheme.menu_color - 40;
		    continue;
		}

		if (chooce == 2) {
		    printf("\e[?25h");
		    return pwd;
		}

		if (chooce == 4) {

		    if (select == 0) {
			sprintf(msg, "请选择文件！！！", NULL);
			if (chooce > 1) {
			    if (cs == 1) {
				menu[chooce][19] = 0;
				chooce = 0;
			    }
			    if (cs == 2) {
				menu[chooce][19] = 0;
				chooce = 1;
			    }
			    mode[1][0] = usetheme.box - 40;
			    mode[0][0] = usetheme.menu_color - 40;
			    continue;
			}

			if (chooce == 0)
			    for (n = 0; n < total; n++) {
				files[n][253] = 0;
				files[n][254] = 0;
				select = 0;
			    }

		    }
		    if (select != 0) {
			tmp = 0;
			for (n = 0; n < total; n++)
			    if (files[n][253] == '\241'
				&& files[n][254] == '\314') {
				for (l = 0; l < strlen(files[n]);
				     l++, tmp++)
				    fc[tmp] = files[n][l];
				fc[tmp] = '/';
				tmp++;
			    }
			for (; tmp <= fcsize; tmp++)
			    fc[tmp] = 0;
			printf("\e[?25h");
			return pwd;

		    }
		}

		if (chooce == 3) {
		    sprintf(msg,
			    "暂无说明。                        Version: 1.6",
			    NULL);
		    continue;
		}


		if (chooce == 5)
		    printf("\e[?25h");
		return "EXIT";

	    }
//end enter
//mode 
	    if (key == usetheme.menu) {
		mode[1][0] = usetheme.box - 40;
		menu[6][19] = usetheme.menu_color - 40;

		if (chooce > 1) {
		    if (cs == 1) {
			menu[chooce][19] = 0;
			chooce = 0;
		    }
		    if (cs == 2) {
			menu[chooce][19] = 0;
			chooce = 1;
		    }
		}

		if (chooce == 0)
		    for (n = 0; n < total; n++) {
			files[n][253] = 0;
			files[n][254] = 0;
			select = 0;
		    }
		if (chooce == 0)
		    sprintf(msg, "只选择一个文件。", NULL);
		if (chooce == 1)
		    sprintf(msg, "可以选择多个文件。", NULL);




		continue;
	    }
// end mode
	}
// mode theme
	if (menu[6][19] == usetheme.menu_color - 40) {
	    key = getch();
//kill
	    if (key == KILL) {
		printf("\e[?25h");
		default_theme =
		    fopen
		    ("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_default_theme.conf",
		     "w");
		fprintf(default_theme, "Default_Theme = %d\n", theme);
		fclose(default_theme);
		return "KILL";
	    }
//end kill
//down
	    if (key == usetheme.down) {
		if (theme < 3) {
		    menu[theme + 6][19] = 0;
		    theme++;
		} else {
		    menu[theme + 6][19] = 0;
		    theme = 1;
		}
		if (theme == 1)
		    usetheme = purple;
		if (theme == 2)
		    usetheme = green;
		if (theme == 3)
		    usetheme = self;
		menu[6][19] = usetheme.menu_color - 40;
		mode[0][0] = usetheme.box - 40;
		mode[1][0] = usetheme.box - 40;

		if (theme == 1)
		    sprintf(msg, "紫色梦幻,Made By Netcan", NULL);
		if (theme == 2)
		    sprintf(msg, "靛青主题,For HNHH By Netcan", NULL);
		if (theme == 3)
		    sprintf(msg, "%s主题,Made By %s", themename, author);


	    }
//end down
// up
	    if (key == usetheme.up) {
		if (theme > 1) {
		    menu[theme + 6][19] = 0;
		    theme--;
		} else {
		    menu[theme + 6][19] = 0;
		    theme = 3;
		}
		if (theme == 1)
		    usetheme = purple;
		if (theme == 2)
		    usetheme = green;
		if (theme == 3)
		    usetheme = self;
		menu[6][19] = usetheme.menu_color - 40;
		mode[0][0] = usetheme.box - 40;
		mode[1][0] = usetheme.box - 40;
		if (theme == 1)
		    sprintf(msg, "紫色梦幻,Made By Netcan", NULL);
		if (theme == 2)
		    sprintf(msg, "靛青主题,For HNHH By Netcan", NULL);
		if (theme == 3)
		    sprintf(msg, "%s主题,Made By %s", themename, author);
	    }
//end up
//enter
	    if (key == usetheme.enter || key == usetheme.menu) {
		menu[6][19] = usetheme.box - 40;
		mode[0][0] = usetheme.menu_color - 40;
		default_theme =
		    fopen
		    ("/mnt/UsrDisk/NetCan-Soft/Settings/fcs_default_theme.conf",
		     "w");
		fprintf(default_theme, "Default_Theme = %d\n", theme);
		fclose(default_theme);
	    }




	}
//end theme


    }


}
