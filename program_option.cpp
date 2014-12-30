// Copyright Shun Terabayashi 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <iterator>
#include <boost/program_options.hpp>

int main(int ac,char* av[])
{

    namespace po = boost::program_options;
    
    // オプションの宣言
    po::options_description options1("Miku is cute");
    options1.add_options()
	("help","Produce help message.")// $ ./mikukawaii --help
	("miku","Miku is so cute.") // $ ./mikukawaii --miku
	("diva,d","Miku is deva.")  // $ ./mikukawaii --diva (or -d)
	("cuteness,c",po::value<int>(),"Set Miku's cuteness.\nPlease set value in 75-100") // $ ./mikukawaii --cuteness 100 (or -c 100)
	;

    // オプションの値を読み込む
    po::variables_map vm;
    
    try{
        // コマンドライン引数をvmに格納
	po::store(po::parse_command_line(ac,av,options1),vm);
	
	po::notify(vm);

	// オプション"help"が指定された時の動作
	if(vm.count("help"))
	{
	    std::cout << options1 << std::endl;
	    return 0;
	}

	// オプション"miku"が指定された時の動作
	if(vm.count("miku"))
	{
	    std::cout << "Set option as miku." << std::endl;
	    std::cout << "Miku is so cute." << std::endl;
	    return 0;
	}
    
	// オプション"diva"が指定された時の動作
	if(vm.count("diva"))
	{
	    std::cout << "Set option as diva." << std::endl;
	    std::cout << "Miku is the cutest in the world." << std::endl;
	    return 0;
	}

	// オプション"cuteness"が指定された時の動作
	if(vm.count("cuteness"))
	{
	    int cuteness = vm["cuteness"].as<int>();
	    if(cuteness >= 75 && cuteness <= 100)
	    {
		std::cout << "Set Miku's cuteness as " << vm["cuteness"].as<int>() << std::endl;
	    }else{
		// おかしな値が入力された場合
		std::cout << "Error:Invalid value." << std::endl;
		if(cuteness < 75)
		{
		    std::cout << "Do you mean other Miku?" << std::endl;
		}
		if(cuteness > 100)
		{
		    std::cout << "Okey. I really understand how you feel." << std::endl;
		    std::cout << "But, please set value in 75-100." << std::endl;
		}
	    }
	}
	else{
	    std::cout << options1 << std::endl;
	}
    }

    // 想定外のオプションが指定された場合
    catch(std::exception &e)
    {
	std::cerr << "Error:" << e.what() << std::endl;
	std::cerr << options1 << std::endl;
	return 1;
    }
    catch(...)
    {
	std::cerr << "Exception of unknown type." <<std::endl;
    }

    return 0;
}
