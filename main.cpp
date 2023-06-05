#include <fstream>
#include <iostream>
#include <filesystem>
#include"User.h"
#include"Message.h"

//=======================������!!!=====================
//���������� ������ ������ � ����� ����� ��������������
//����, �� �.�. ������� ������ ���������, � ��� VS 2017
//������������ ���������� ���������� <filesystem>, ���
// �����, ����� ����. �������� ����������������� 
// ����������� � https://www.onlinegdb.com/

void demo_perms(std::filesystem::perms p)
{
    using std::filesystem::perms;
    auto show = [=](char op, perms perm)
    {
        std::cout << (perms::none == (perm & p) ? '-' : op);
    };
    show('r', perms::owner_read);
    show('w', perms::owner_write);
    show('x', perms::owner_exec);
    show('r', perms::group_read);
    show('w', perms::group_write);
    show('x', perms::group_exec);
    show('r', perms::others_read);
    show('w', perms::others_write);
    show('x', perms::others_exec);
    std::cout << '\n';
}

int main()
{      
    std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
    if (!user_file)
        // ��� �������� ����� ���������� �������� ios::trunc
        user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);
    // ������������� ����������� ����� ��� �����
    std::filesystem::permissions(
        "users.txt",
        std::filesystem::perms::owner_all
    );
    std::filesystem::permissions(
        "users.txt",
        std::filesystem::perms::group_all | std::filesystem::perms::others_all,
        std::filesystem::perm_options::remove);

    if (user_file) {
        User user("Alex", "qwerty", "12345");
        // ������� ������ �� � ����
        user_file << user << std::endl;
        // ����� ������� ������ �� �����, ���� ���������� ������� ��� ������ � ������ �����
        user_file.seekg(0, std::ios_base::beg);
        // ��������� ������ �� �����
        user_file >> user;
        std::cout << user << std::endl;
    }
    else
    {
        std::cout << "Could not open file!" << '\n';
        return 0;

    }

    // ���������� ������� ���� ��� ������ Message
    std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);
    if (!message_file)
        // ��� �������� ����� ���������� �������� ios::trunc
        message_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::trunc);
    // ������������� ����������� ����� ��� �����
    std::filesystem::permissions(
        "messages.txt",
        std::filesystem::perms::owner_all
    );
    std::filesystem::permissions(
        "messages.txt",
        std::filesystem::perms::group_all | std::filesystem::perms::others_all,
        std::filesystem::perm_options::remove);

    if (message_file) {
        Message message("Hello!", "Alex", "Maria");
        // ������� ������ �� � ����
        message_file << message << std::endl;
        // ����� ������� ������ �� �����, ���� ���������� ������� ��� ������ � ������ �����
        message_file.seekg(0, std::ios_base::beg);
        // ��������� ������ �� �����
        message_file >> message;
        std::cout << message << std::endl;
    }
    else
    {
        std::cout << "Could not open file!" << '\n';
        return 0;
    }

    // ��������� ����� ����� ������
    std::cout << "users.txt: ";
    demo_perms(std::filesystem::status("users.txt").permissions());
    std::cout << "messages.txt: ";
    demo_perms(std::filesystem::status("messages.txt").permissions());
}