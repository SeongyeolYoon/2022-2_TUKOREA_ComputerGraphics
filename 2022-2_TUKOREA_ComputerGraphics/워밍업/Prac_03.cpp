#include <iostream>
#include <string>
#include <fstream>

int main()
{
	bool onToggleD{ false };
	bool onToggleE{ false };
	bool onToggleF{ false };
	bool isPressG{ false };
	bool isPressH{ false };

	std::string fileName;

	while (true) {
		std::cout << "Input file name:";
		std::cin >> fileName;
		if (std::cin.fail()) {
			std::cout << "please try agian" << std::endl;
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			break;
	}

	std::ifstream ifs{ fileName };

	while (true) {
		if (!ifs) {
			std::cout << "Cannot open file!" << std::endl;
			return 0;
		}
		else {
			while (true) {
				std::ifstream ifs{ fileName };
				system("cls");
				while (ifs) {
					std::string str;
					std::getline(ifs, str);
					std::cout << str << std::endl;
				}

				std::cout << "d: Flip the whole sentence" << std::endl;
				std::cout << "e: Inserting a certain number of spaces at equal intervals" << std::endl;
				std::cout << "f: Flip characters by spacing" << std::endl;
				std::cout << "g: Replace certain characters inside the character with other characters, receive new characters to enter" << std::endl;
				std::cout << "h: To print out how many letters are the same when reading before or after reading" << std::endl;
				std::cout << "q: EXIT" << std::endl;
				std::cout << "Input command:";

				char command;

				while (true) {
					std::cin >> command;

					if (std::cin.fail()) {
						std::cout << "please try agian" << std::endl;
						std::cin.clear();
						std::cin.ignore(32767, '\n');
					}
					else
						break;
				}

				switch (command)
				{
				case 'd':
					onToggleD = !onToggleD;
					break;
				case 'e':
					onToggleE = !onToggleE;
					break;
				case 'f':
					onToggleF = !onToggleF;
					break;
				case 'g':
					isPressG = !isPressG;
					break;
				case 'h':
					isPressH = !isPressH;
					break;
				case 'q':
					exit(1);
					break;
				default:
					break;
				}

				// ����ؾ��� �κ�
				if (onToggleE) {
					if (onToggleD) {
						// E,D,F ��� ����
						if (onToggleF) {

							// D, F �����ϰ� �������� E �����ϸ� �� �� ? 
							std::ifstream ifs{ fileName };

							while (ifs) {
								int wordCount{ };
								std::string str;
								std::getline(ifs, str);
								std::reverse(str.begin(), str.end());

								std::string token{ " " };
								int curPosition = 0;
								int position;

								while ((position = str.find(token, curPosition)) != std::string::npos) {
									int len = position - curPosition;
									std::string result = str.substr(curPosition, len);

									for (int i = result.size(); i >= 0; --i) {
										std::cout << result[i];
										wordCount++;
										if (3 == wordCount) {
											std::cout << "@@";
											wordCount = 0;
										}
									}
									std::cout << " ";
									curPosition = position + 1;
								}
								wordCount = 0;

								std::string result = str.substr(curPosition);
								for (int i = result.size(); i >= 0; --i) {
									std::cout << result[i];
									wordCount++;
									if (3 == wordCount) {
										std::cout << "@@";
										wordCount = 0;
									}
								}
								std::cout << std::endl;
							}
						}
						// E, D ����
						else {
							std::ifstream ifs{ fileName };

							while (ifs) {
								int wordCount{ };
								std::string str;
								std::getline(ifs, str);
								char changed, change;

								for (int i = str.length()-1; i >= 0; --i) {
										std::cout << str[i];
									wordCount++;
									if (3 == wordCount) {
										std::cout << "@@";
										wordCount = 0;
									}
								}
								std::cout << std::endl;
							}
						}
					}
					else {
						// E, F ����
						if (onToggleF) {

							std::ifstream ifs{ fileName };

							while (ifs) {
								std::string str;
								std::getline(ifs, str);
								std::string token{ " " };
								int curPosition = 0;
								int position;
								int wordCount{ };

								while ((position = str.find(token, curPosition)) != std::string::npos) {
									int len = position - curPosition;
									std::string result = str.substr(curPosition, len);
									for (int i = result.size()-1; i >= 0; --i) {
										wordCount++;
										std::cout << result[i];
										if (3 == wordCount) {
											std::cout << "@@";
											wordCount = 0;
										}
									}
									std::cout << " ";
									curPosition = position + 1;
								}
								std::string result = str.substr(curPosition);
								for (int i = result.size(); i >= 0; --i) {
									wordCount++;
									std::cout << result[i];
									if (3 == wordCount) {
										std::cout << "@@";
										wordCount = 0;
									}
								}
								wordCount = 0;
								std::cout << std::endl;
							}
						}
						// E �� ����
						else {
							std::ifstream ifs{ fileName };

							while (ifs) {

								int wordCount{ };
								std::string str;
								std::getline(ifs, str);
								
								for (int i = 0; i < str.length(); ++i) {
									std::cout << str[i];
									wordCount++;
									if (3 == wordCount) {
										std::cout << "@@";
										wordCount = 0;
									}
								}
								std::cout << std::endl;
							}
						}
					}
				}
				else {
					if (onToggleD) {

						// D, F ����
						// ������ D -> F�� ����
						// �켱 ������ ���¿���, ���� ������ �ٽ� ������
						if (onToggleF) {
							std::ifstream ifs{ fileName };

							while (ifs) {
								std::string str;
								std::string temp;
								std::string token{ " " };
								std::getline(ifs, str);
								str.append(token);
								std::reverse(str.begin(), str.end());

								int curPosition = 0;
								int position;

								while ((position = str.find(token, curPosition)) != std::string::npos) {
									int len = position - curPosition;
									std::string result = str.substr(curPosition, len);

									for (int i = result.size(); i >= 0; --i) {
										std::cout << result[i];
									}
									std::cout << " ";
									curPosition = position + 1;
								}
								std::string result = str.substr(curPosition);
								for (int i = result.size(); i >= 0; --i) {
									std::cout << result[i];
								}
								std::cout << std::endl;
							}

						}
						// D�� ����
						else {
							std::ifstream ifs{ fileName };

							while (ifs) {
								int wordCount{ };
								std::string str;
								std::getline(ifs, str);

								for (int i = str.length(); i >= 0; --i)
									std::cout << str[i];

								std::cout << std::endl;
							}
						}
					}
					else {
						// F�� ����
						if(onToggleF){
							std::ifstream ifs{ fileName };

							while (ifs) {
								std::string str;
								std::getline(ifs, str);
								std::string token{ " " };
								str.append(token);
								char changed, change;
								int asymmetryIndex{ };
								int symmetryCount{ };
								bool isBiSymmetry{ true };
								int curPosition = 0;
								int position;

								while ((position = str.find(token,curPosition)) != std::string::npos) {
									int len = position - curPosition;
									std::string result = str.substr(curPosition, len);
									
									for (int i = result.size(); i >= 0; --i) {
										if (isPressG) {
											while (true) {
												std::cout << "��ü�Ǵ� ���ڿ� ��ü�� ���� �Է�:";
												std::cin >> changed >> change;

												if (std::cin.fail()) {
													std::cout << "�ٽ� �Է����ּ���" << std::endl;
													std::cin.clear();
													std::cin.ignore(32767, '\n');
												}
												else
													break;
											}
											if (changed == result[i])
												result[i] = change;
											std::cout << result[i];
										}
										else
											std::cout << result[i];
									}
									std::cout << " ";
									curPosition = position + 1;
								}

								std::cout << std::endl;
							}
						}
						// E, D, F �ƹ��͵� ���� X
						else {
						// G�� ����
							if (isPressG) {
								std::ifstream ifs{ fileName };
								char change;
								char changed;

								while (true) {
									std::cout << "��ü�Ǵ� ���ڿ� ��ü�� ���� �Է�:";
									std::cin >> changed >> change;

									if (std::cin.fail()) {
										std::cout << "�ٽ� �Է����ּ���" << std::endl;
										std::cin.clear();
										std::cin.ignore(32767, '\n');
									}
									else
										break;
								}

								while (ifs) {
									std::string str;
									std::getline(ifs, str);
									for (int i = 0; i < str.length(); ++i) {
										if (changed == str[i])
											str[i] = change;
										std::cout << str[i];
									}
									std::cout << std::endl;
								}
								isPressG = !isPressG;
							}
							// H�� ����
							else if (isPressH) {
								std::ifstream ifs{ fileName };
								while (ifs) {
									int asymmetryIndex{ };
									int symmetryCount{ };
									bool isBiSymmetry{ true };
									std::string str;
									std::getline(ifs, str);
									str.erase(str.length());

									for (int i = 0; i < str.length() / 2; ++i) {
										// ��Ī ���ڿ����� �˻�
										// ����,��Ī ���ڿ��̸� 
										// (ù �����ε��� + ������ �ε���) /2 �ε����� �����ϰ�
										// ���� �ε��� ������ ����Ѵ�.

										// NOTE : ��Ī �˻� ������ �ٲ�� �� �� �� ����
										// ��Ī ���ڰ� �ƴϸ�
										if (str[i] != str[str.length() - 1 - i]) {
											asymmetryIndex = i;
											break;
										}
										// ��Ī ���ڰ� �´ٸ�
										else {
											symmetryCount++;
											continue;
										}
									}
									if (symmetryCount >= 2) {
										isBiSymmetry = true;

										for (int i = 0; i < str.length(); ++i) {
											std::cout << str[i];
										}

										std::cout << ": ";

										// int midIndex =(0 + str.length()) / 2;

										if (isBiSymmetry) {
											if (0 != asymmetryIndex) {
												for (int i = 0; i < asymmetryIndex; ++i) {
													std::cout << str[i];
												}
											}
											else {
												for (int i = 0; i < str.length() / 2; ++i) {
													std::cout << str[i];
												}
											}
										}
										std::cout << std::endl;
									}
									else {
										isBiSymmetry = false;
										if (!isBiSymmetry) {
											for (int i = 0; i < str.length(); ++i) {
												std::cout << str[i];
												if (str.length() - 1 == i)
													std::cout << ": 0" << std::endl;
											}
										}
									}
									std::cout << std::endl;
								}
								isPressH = !isPressH;
							}
							// �ƹ��͵� ������ �ȵǾ� ������.
							else {
								std::ifstream ifs{ fileName };
								while (ifs) {
									std::string str;
									std::getline(ifs, str);
									std::cout << str << std::endl;
								}
							}
						}
					}
				}
				system("pause");
			}
		}
	}
}