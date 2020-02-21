This project used dictionaries in various ways, such as dynamic programming (memoization), finding common words between files, solve the "Car Talk" puzzle (identifying words that have the same phonetic pronounciation when a letter is removed), and finding anagrams.
The files I contributed to were fib.cpp, common_words.h, common_words.cpp, cartalk_puzzle.cpp
    fib.cpp: Use the concept of memoization in dynamic programming to make computing a Fibonacci number more efficient.
        1) implemented two fibonacci sequence functions, one memoized and one standard.
    common_words.cpp, common_words.h: find common words between different files
         1) init_file_word_maps(): initalize standard maps containing the words and their frequencies within a file.
         2) init_common(): initialize a standard map containing the number of files a word appears in
         3) get_common_words(): finds all words that appear more than "n" (input value) times and in all files
    cartalk_puzzle.cpp, pronounce_dict.h, and pronounce_dict.cpp: find solutions to the Car Talk puzzle
         1) homophones(): identifies if two words are homophones or not
         2) cartalk_puzzle(): solves the Car Talk puzzle
    anagram_dict.h and anagram_dict.cpp: makes a dictionary and looks for anagrams for different words.
        1) get_anagrams(): returns anagrams of a given word by looking through a dictionary of anagrams
        2) get_all_anagrams(): find anagrams of all strings in a vector
This project was completed for CS225. All materials not mentioned were provided by course staff.