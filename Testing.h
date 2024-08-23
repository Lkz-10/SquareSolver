#ifndef __TESTING_H__
#define __TESTING_H__

/**
* @brief                 ��������� ������������� � ������
* @param a               ������� ����������� ���������
* @param b               ������ ����������� ���������
* @param c               ��������� ���� ���������
* @param x1_expexted     ������ ������ ���������
* @param x2_expected     ������ ������ ���������
* @param nRoots_expected ���������� ������ ���������
*/
struct coeffsStruct
{
    double a;
    double b;
    double c;
    double x1_expected;
    double x2_expected;
    int nRoots_expected;
};

/**
* @brief              �������, ����������� ��������� �� �������� �����
* @param nTest        ����� �����
* @param structData   ���������, ���������� ������ ��� ������������
* @return             0 ��� �������� ����������� �����, -1 ��� ������
*/
int Test(int nTest, struct coeffsStruct* structData);

/**
* @brief        �������, ����������� ������ ��������� ������� ��� ������������
*/
void CreateTests ();

/**
* @brief        �������, ����������� �����
* @param tests  ������ � ������� ��� ������
*/
void RunAllTests(coeffsStruct tests[]);

#endif
