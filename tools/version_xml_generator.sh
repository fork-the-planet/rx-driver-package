#!/bin/sh

gawk '
BEGIN {
	# �O�����
	#   1) �eFIT���W���[���t�H���_�ォ����s�����
	#   2) �eFIT���W���[���ɂ�Makefile�����݂��Ă���A�����Ƀo�[�W������񂪏����Ă���
	#   3) �eFIT���W���[����2�K�w��ʂ�tools�t�H���_������A�{�t�@�C���͂����Ɋi�[�����
	# 
	# ����
	#   1) FIT���W���[�����ƃo�[�W������񂪏����Ă���FIT���W���[������Makefile�̃p�X���
	#   2) $(release_tag_commit_number) ��: 8dadb91c0486eaa03af224c935eedb9bb2df69a3
	#     -> v1.25���̃R�~�b�g�ԍ�
	#       https://github.com/renesas/rx-driver-package/releases/tag/V1.25
	#
	# ��������
	#   2024/4/11
	#     emWin FIT���W���[����zip�t�@�C�����v�b�V������T�C�Y�̏��100MB���z�������߁A
	#     ���������W���[���̓����[�X�^�O�̃A�Z�b�g�փ��W���[����u�����j�Ƃ���
	#     �z�������W���[����URL�����N�̓A�Z�b�g���w���悤�R�[�h��ǉ�
	#
	# ���s��
	#   sh ../../tools/version_xml_generator.sh Makefile release_tag_commit_number=8dadb91c0486eaa03af224c935eedb9bb2df69a3
	
	# �萔�f�[�^
	rdp_repo_url = "https://raw.githubusercontent.com/renesas/rx-driver-package"
	rdp_release_url = "https://github.com/renesas/rx-driver-package/releases/download"

	# LFS���߃��W���[��(100MB�ȏ�̃��W���[��)
	# ����emWin FIT�̂݁A����100MB�𒴂��郂�W���[�����������ꍇ�̓X�y�[�X�Ōq���ŋL�q����
	# �� "r_emwin_rx r_xxxx_rx"
	split( "r_emwin_rx" , lfs_excess_modules, " " );

	while(1)
	{
		if(ARGC != 4)
		{
			printf("error: 3 aruguments are needed. arg number = %d\n", ARGC - 1);
			for(i=1; i<ARGC; i++)
			{
				printf("arg[%d]=%s\n",i, ARGV[i]);
			}
			break;
		}
		
		if(0 == getline)
		{
			/* end of file */
			break;
		}
		
		if($1 == "MODULE_NAME")
		{
			module_name = $3;
#			printf("module_name found: %s\n", module_name);
		}

		if($1 == "VERSION")
		{
			module_version = $3;
			module_version_str = module_version;
#			printf("module_version found: %s\n", module_version);
		}

		#���W���[���o�[�W�����ƃt�@�C�����̃o�[�W�����\�L���قȂ�ꍇ�Amodule_version_str��ݒ�
		if($1 == "VERSION_STR")
		{
			module_version_str = $3;
#			printf("module_version string found: %s\n", module_version_str);
		}

		
		if($1 == "MDF")
		{
			test = $3;

			if(test ~ /NOT_SUPPORTED/)
			{
				mdf_support_flag = 0;
			}
			else if(test ~ /V1,V2/)
			{
				mdf_support_flag = 3;
			}
			else if(test ~ /V1/)
			{
				mdf_support_flag = 1;
			}
			else if(test ~ /V2/)
			{
				mdf_support_flag = 2;
			}
			else
			{
				mdf_support_flag = 0;
			}

		}
		parse_ok_flag = 1;
	}
	
	if(parse_ok_flag == 1)
	{
		input_release_tag_commit_number_string = ARGV[2];
		input_release_tag_commit_number_depth = split(input_release_tag_commit_number_string, input_release_tag_commit_number_string_array, /=/);
		release_tag_commit_number = input_release_tag_commit_number_string_array[input_release_tag_commit_number_depth];
	#	printf("module commit number found: %s\n", release_tag_commit_number);
		input_release_tag_commit_version_string = ARGV[3];
		input_release_tag_commit_version_depth = split(input_release_tag_commit_version_string, input_release_tag_commit_version_string_array, /=/);
		release_tag_commit_version = input_release_tag_commit_version_string_array[input_release_tag_commit_version_depth];

		zip_file_name = sprintf("%s_v%s.zip", module_name, module_version_str);
	#	printf("%s\n", zip_file_name);

		xml_file_name = sprintf("%s_v%s.xml", module_name, module_version_str);
	#	printf("%s\n", xml_file_name);

		if(mdf_support_flag == 1)
		{
			mdf_file_name = sprintf("%s_v%s.mdf", module_name, module_version_str);
		}
		else if(mdf_support_flag == 2)
		{
			mdf_file_name = sprintf("%s_v%s_extend.mdf", module_name, module_version_str);
		}
		else if(mdf_support_flag == 3)
		{
			mdf_file_name_v1 = sprintf("%s_v%s.mdf", module_name, module_version_str);
			mdf_file_name_v2 = sprintf("%s_v%s_extend.mdf", module_name, module_version_str);
		}
		else
		{
			mdf_file_name = "";
		}
	#	printf("%s\n", mdf_file_name);

		depth = 1;
		
		print_indent(depth);
		# printf("<module>\r\n");
		printf("<module rdp_version=\"%s\">\r\n", release_tag_commit_version);
		depth++;
		
		print_indent(depth);
		printf("<name>");
		printf("%s", module_name);
		printf("</name>\r\n");

		print_indent(depth);
		printf("<version>");
		printf("%s", module_version);
		printf("</version>\r\n");
		
		print_indent(depth);
		printf("<urls>\r\n");
		depth++;

		print_indent(depth);

		if(1 == check_excess_module(module_name))
		{
			#�ʏ탂�W���[���̏ꍇ
			printf("<url>%s/%s/FITModules/%s</url>\r\n", rdp_repo_url, release_tag_commit_number, zip_file_name);
			print_indent(depth);
			printf("<url>%s/%s/FITModules/%s</url>\r\n", rdp_repo_url, release_tag_commit_number, xml_file_name);
			if(mdf_support_flag != 0)
			{
				if(mdf_support_flag == 3)
				{
					print_indent(depth);
					printf("<url>%s/%s/FITModules/%s</url>\r\n", rdp_repo_url, release_tag_commit_number, mdf_file_name_v1);
					print_indent(depth);
					printf("<url>%s/%s/FITModules/%s</url>\r\n", rdp_repo_url, release_tag_commit_number, mdf_file_name_v2);
				}
				else
				{
					print_indent(depth);
					printf("<url>%s/%s/FITModules/%s</url>\r\n", rdp_repo_url, release_tag_commit_number, mdf_file_name);
				}
			}
		}
		else
		{
			#LFS���߃��W���[���̏ꍇ
			printf("<url>%s/V%s/%s</url>\r\n", rdp_release_url, release_tag_commit_version, zip_file_name);
			print_indent(depth);
			printf("<url>%s/V%s/%s</url>\r\n", rdp_release_url, release_tag_commit_version, xml_file_name);
			if(mdf_support_flag != 0)
			{
				if(mdf_support_flag == 3)
				{
					print_indent(depth);
					printf("<url>%s/V%s/%s</url>\r\n", rdp_release_url, release_tag_commit_version, mdf_file_name_v1);
					print_indent(depth);
					printf("<url>%s/V%s/%s</url>\r\n", rdp_release_url, release_tag_commit_version, mdf_file_name_v2);
				}
				else
				{
					print_indent(depth);
					printf("<url>%s/V%s/%s</url>\r\n", rdp_release_url, release_tag_commit_version, mdf_file_name);
				}
			}
		}

		depth--;
		
		print_indent(depth);
		printf("</urls>\r\n");
		depth--;
		
		print_indent(depth);
		printf("</module>\r\n");
		depth--;
	}
}
function print_indent(depth)
{
    # if���̐[���ɂ��C���f���g����
    for(j=0; j<depth; j++) {
        printf("  ");
    }
}
function check_excess_module(module)
{
	for(i in lfs_excess_modules) {
		if(lfs_excess_modules[i] == module) {
			return 0;
		}
	}
	return 1;
}

' $*
