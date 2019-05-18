#include<bits/stdc++.h>
#include<cstdlib>
#include<ctime>

using namespace std;
int m = 8;
string plain_text;
string key;
ofstream output;
//vector<string> final_modified_keys(16);
//vector<string> decrypt_keys(16);

string convert_a_char(char ch){
	int n = (int) ch;
	int kn = 2;
	
	char temp_buff[8];
	int div = 1;
	int s;
	for(int i = 0; i < 8; i++){
		s = (n >>(7-i)&1);

		temp_buff[i] = '0' + s;
		
	}
	string rt(temp_buff);

	return rt;
}

vector<string> convert_a_string_to_binary_rep(string data_string){
	// char temp[8];
	//string temp;
	vector<string> dt_block((int) (data_string.size()/m));
	//output << data_string << endl;
	string row = "";
	int cnt = 0;
	int letter_count = 0;
	for(int i = 0; i < data_string.size(); i++){
		string temp = convert_a_char(data_string[i]);
		row += temp;
		letter_count++;
		//dt_block[cnt] = row;
		if((i%m) == m-1){
			//output << "Row - " << cnt << " Data : " << row << " l_count: " << letter_count << " Bit count : " << row.size() << endl;
			letter_count = 0;
			dt_block[cnt++] = row;
			row = "";
		}
		//reverse(temp.begin(),temp.end());
		//output << temp << endl;
		
	}
	output << "data block <ascii of 8 characters per row> " << endl;
	for(int i = 0; i < dt_block.size(); i++){
		output << dt_block[i] << endl;
	}
	return dt_block;
}


vector<string> Initial_Transposition(vector<string> data_block){
	
	int PI_arr[64] = {58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7};

    vector<string> transposed_dt_block(data_block.size());
    char tmp[64];
    
    int cnt = 0;
    tmp[64] = '\0'; 
    for(int i = 0; i < data_block.size(); i++){
    	for(int j = 0; j < data_block[i].size(); j++){
    		tmp[j] = data_block[i][PI_arr[j]-1];
    		
    		
    	}
    	// for(int k = 0; k < 64; k++){
    	// 	output << "Temp Position: " << k << " Element: " << tmp[k] << " Org pos: " << PI_arr[k]-1 << " Elem: " << data_block[i][PI_arr[k]-1] << endl;
    	// }

    	output << endl; 
    	string temp(tmp);
    	//output << temp << " " << temp.size() << endl;
    	transposed_dt_block[i] = temp;

    }
    output << "After Initial_Transposition of data block" << endl;

    for(int i = 0; i < transposed_dt_block.size(); i++){
    	output << transposed_dt_block[i] << endl;
    }

    return transposed_dt_block;
}


// In-place rotates s towards left by d 
void leftrotate(string &s, int d) 
{ 
    reverse(s.begin(), s.begin()+d); 
    reverse(s.begin()+d, s.end()); 
    reverse(s.begin(), s.end()); 
} 
  
// In-place rotates s towards right by d 
void rightrotate(string &s, int d) 
{ 
   leftrotate(s, s.length()-d); 
} 


string key_generator_along_step(int step, string key){
	
	string l_key = "", r_key = "";
	for(int i = 0; i < key.size(); i++){
		if(i < 28){
			l_key += key[i];
		}
		else{
			r_key += key[i];
 		}
	}

	// output << "Applying 28 bit Left-Right division in the key" << endl;
	// output << endl;

	// output << "L: " << l_key << l_key.size()  << " R: " << r_key << r_key.size() << endl;

	leftrotate(l_key,step);
	leftrotate(r_key,step);

	// output << endl;
	// output << "After Rotation  of " << step << " iteration " << endl;
	// output << endl;

	// output << "L: " << l_key << l_key.size()  << " R: " << r_key << r_key.size() << endl;
	// output << endl;

	string modified_key = l_key + r_key;

	return modified_key;


}

vector<string> key_generator(string key){
	int CP_1[56] = {57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4};

    int CP_2[48] = {14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32};

    int SHIFT[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1}; 

    vector<string> final_modified_keys(16);

    vector<string> temp_key_holder = convert_a_string_to_binary_rep(key);
    string key_bin = temp_key_holder[0];

    char tmp[56];
    
    // int cnt = 0;
    tmp[56] = '\0'; 
    
	for(int j = 0; j < 56; j++){
		tmp[j] = key_bin[CP_1[j]-1];
	
	}
	// for(int k = 0; k < 64; k++){
	// 	output << "Temp Position: " << k << " Element: " << tmp[k] << " Org pos: " << PI_arr[k]-1 << " Elem: " << data_block[i][PI_arr[k]-1] << endl;
	// }
	string key_transposed(tmp);

	output << endl;
	output << "Key after transposition: \n"  << key_transposed << endl;
	output << endl;

	string modified_key;

	char key_temp[48];
	key_temp[48] = '\0';

	

	for(int i = 1; i <= 16; i++){
		modified_key = key_generator_along_step(SHIFT[i-1],key_transposed);

		// output << "modified_key after CP_1 transposition and rotation at " << i << " iteration: " << endl;
		// output << modified_key << endl;

		for(int j = 0; j < 48; j++){
			key_temp[j] = modified_key[CP_2[j]-1];
	
		}

		string mod_key(key_temp);
		final_modified_keys[i-1] = mod_key;

		// if(i == 1 || i == 16){
		// 	for(int k = 0; k < 48; k++){
		// 		output << "Temp Position: " << k << " Element: " << key_temp[k] << " Org pos: " << CP_2[k]-1 << " Elem: " << modified_key[CP_2[k]-1] << endl;
		// 	}
		// }

		// output << "After CP_2: " << endl;
		// output  << mod_key << endl; 
	}

	for(int i = 0; i < final_modified_keys.size(); i++){
		//output << "K" << i+1 << " : \n" << final_modified_keys[i] << endl;
	}
	//return key_transposed;

	return final_modified_keys;
    
}

vector<string> decryption_key_generator(vector<string> final_modified_keys){
	vector<string> decrypt_keys(16);

	for(int i = 0; i < 16; i++){
		decrypt_keys[i] = final_modified_keys[15-i];
	}

	return decrypt_keys;

	


}

string XOR_two_bit_string(string a1, string a2){
	if(a1.size() != a2.size()){
		output << "Genjam in XOR function" << endl;
		return 0;
	}
	string XOR_Output = "";
	for(int i = 0; i < a1.size(); i++){
		if(a1[i] != a2[i]){
			XOR_Output += "1";
		}
		else{
			XOR_Output += "0";
		}
	}
	return XOR_Output;
}


string P_BOX(string sampled_PI2){

	int P_Box[32] = {16, 7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26, 5, 18, 31, 10,
     2, 8, 24, 14, 32, 27, 3, 9,
     19, 13, 30, 6, 22, 11, 4, 25};

	char P_box_temp[32];
	P_box_temp[32] = '\0';

	for(int n = 0; n < 32; n++){
		P_box_temp[n] = sampled_PI2[P_Box[n]-1];
	}

	string function_Sim(P_box_temp);

	return function_Sim;


}

vector<string> DES_implementation(vector<string> data_block, vector<string> keys){

	for(int i = 0; i < keys.size(); i++){
		output << "K" << i+1 << " : \n" << keys[i] << endl;
	}

	string l_block_prev = "",r_block_prev = "";
	string used_block = "", l_block_new = "", r_block_new = "";
	int E[48] = {32, 1, 2, 3, 4, 5,
     4, 5, 6, 7, 8, 9,
     8, 9, 10, 11, 12, 13,
     12, 13, 14, 15, 16, 17,
     16, 17, 18, 19, 20, 21,
     20, 21, 22, 23, 24, 25,
     24, 25, 26, 27, 28, 29,
     28, 29, 30, 31, 32, 1};

    int PI_2_arr[32] = {35, 38, 46, 6, 43, 40, 14, 45,
		33, 19, 26, 15, 23, 8, 22, 10, 
		12, 11, 5, 25, 27, 21, 16, 31,
		28, 32, 34, 24, 9, 37, 2, 1};

	vector<string> iterated_data_block(data_block.size());

	output << endl;
	output << "===========================Simulating DES=============================== " << endl;
	output << endl;
	for(int i = 0; i < data_block.size(); i++){
		
		used_block = data_block[i];
		

		for(int j = 0; j < used_block.size(); j++){
			if(j < 32){
				l_block_prev += used_block[j];
			}
			else{
				r_block_prev += used_block[j];
			}

		}


		for(int k = 0; k < 16; k++){
			output << endl;
			output << "-------------Executing " << k << "th iteration on data_block: \n" << used_block << "-------------" << endl;
			
			l_block_new = r_block_prev; // must update r_block_prev and l_block_prev
			
			char e_temp[48];
			e_temp[48] = '\0';

			char PI_2_sampler[32];
			PI_2_sampler[32] = '\0';

			for(int j = 0; j < 48; j++){
				e_temp[j] = r_block_prev[E[j]-1];
			}

			string e_final(e_temp);

			output << "e : \n" << e_final << endl;
			output << "KeyI : \n" << keys[k] << endl;

			string e_KeyI_xor = XOR_two_bit_string(e_final,keys[k]);

			output << "e and KeyI is xored to get: \n" << e_KeyI_xor << endl;

			for(int j = 0; j < 32; j++){
				PI_2_sampler[j] = e_KeyI_xor[PI_2_arr[j]-1];
			}
			PI_2_sampler[32] = '\0';
			string sampled_PI2(PI_2_sampler);

			output << sampled_PI2.size() << " bits sampled from e and keyI xored to get: \n" << sampled_PI2 << endl;

			output << "left block previous: \n" << l_block_prev << endl;
			string function_Sim = P_BOX(sampled_PI2);

			output << "P box Simulation result: \n" << function_Sim << " Size- " << function_Sim.size() << endl;

			r_block_new = XOR_two_bit_string(l_block_prev,function_Sim);

			output << "L_n: " << l_block_new << "  R_n: " << r_block_new << endl;


			l_block_prev = l_block_new;
			r_block_prev = r_block_new;
			output << "-------------------- " << k << "th iteration Executed------------------------" << endl;
			output << endl;


		}

		//output << "L : " << l_block << " " << l_block.size() << " R: " <<  r_block << " " << r_block.size() << endl;
		//output << endl;
		 //output << l_block_prev << " " << r_block_prev << endl;
		 //output << l_block_new << " " << r_block_new << endl;
		l_block_new = r_block_prev;
		r_block_new = l_block_prev;

		iterated_data_block[i] = l_block_new+r_block_new;

		output << "Final Data_Block-" << i << ":" << iterated_data_block[i] << endl;
		output << endl;

		l_block_prev = "";
		r_block_prev = "";
		l_block_new = "";
		r_block_new = "";
		
	}

	return iterated_data_block;
}

vector<string> Final_Permut(vector<string> data_block){

	int PI_1_arr[64] = {40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25};

	char final_permut_temp[64];
	final_permut_temp[64] = '\0';

	vector<string> cipher_text(data_block.size());

	for(int i = 0; i < data_block.size(); i++){
		for(int n = 0; n < 64; n++){
			final_permut_temp[n] = data_block[i][PI_1_arr[n]-1];
		}

	

		string encrypt(final_permut_temp);

		output << "\n\nFinal Permut-" << encrypt <<"\n\n";
		cipher_text[i] = encrypt;
	}

	return cipher_text;


}

int Binary_to_int_converter(string bit){
	unsigned int sum = 0;
	unsigned int idx = 0;  
	int sz = bit.size();

	for(int i = sz-1; i >= 0; i--){
		sum += ((unsigned int) (bit[i]-'0'))*pow(2,idx);
		idx++;
	}
	//out << "Integer: " << sum << endl;
	return sum; 
}

void print_message(vector<string> data_block, int option){
	//printf("%c",48);
	string bit_rep = "";
	char temp;
	string msg = "";
	string row;
	unsigned int num = 0;

	output << "Printing Ciphered Text" << endl;

	for(int i = 0; i < data_block.size(); i++){

		output << "Data_Block : " << data_block[i] << endl;
		row = data_block[i];
		bit_rep = "";
		temp = 0;
		num = 0;
		for(int j = 0; j <= row.size(); j++){
			if(!(j%8) && (j != 0)){
				//output << bit_rep << endl;
				//output << Binary_to_int_converter(bit_rep) << endl;

				num = Binary_to_int_converter(bit_rep);
				temp = (char) num;

				//output << "N:" << num << " ";
				output << num << " ";
				//output << temp;
				msg += temp;
				bit_rep = "";
				temp = 0;

			}
			if(j == row.size()) break;
			bit_rep += row[j];
			
			//output << temp;
		}
		output << endl;

	}
	if(option == 1)	output << "\nencrypted cipher_text: " << msg << endl;
	else{
		output << "Plain_text with Padding: " << msg << endl;
		for(int i = msg.size()-1; i >= 0 ; i--){
			if(msg[i] != '~') break;
			else msg[i] = ' ';
		}
		output << "\ndecrypted plain_text: " << msg << endl;

	} 
}	


int main(){

	// char plain_text[100];
	output.open("Output.txt");
	
	if(!output.is_open()){
		output << "Error in File Opening" << endl;

		return -1;
	}


	cout << "Enter Plain Text: " ;

	getline(cin,plain_text);

	cout << "Enter Key: ";

	getline(cin,key);

	
	
	int cnt = (plain_text.size() % m);
	if(!cnt){
		//output << "No padding" << endl;
	}
	else{
		//output << "Need Padding " << (m-cnt) << endl;
		for(int i = 1; i <= (m-cnt); i++){
			plain_text += "~";
		}
	}

	output << plain_text << endl;
	output << endl;
	vector<string> data_block = convert_a_string_to_binary_rep(plain_text);
	output << endl;

	vector<string> reserve_db  = data_block;

	data_block = Initial_Transposition(data_block);

	vector<string> final_modified_keys =  key_generator(key);

	vector<string> iterated_data_block = DES_implementation(data_block,final_modified_keys);

	for(int i = 0; i < iterated_data_block.size(); i++){
		output << iterated_data_block[i] << endl;
	}

	vector<string> cipher_text = Final_Permut(iterated_data_block);

	

	print_message(cipher_text,1);

	//Decryption Try...

	vector<string> inv_data_block = Initial_Transposition(cipher_text);

	vector<string> decrypt_keys = decryption_key_generator(final_modified_keys);

	vector<string> iterated_data_block_decrypt = DES_implementation(inv_data_block,decrypt_keys);

	vector<string> decrypt_text = Final_Permut(iterated_data_block_decrypt);

	print_message(decrypt_text,2);

	cout << "Done" << endl;




}
