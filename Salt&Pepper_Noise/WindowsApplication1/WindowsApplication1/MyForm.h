#pragma once
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <iostream>

namespace WindowsApplication1
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// MyForm ���K�n
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  �b���[�J�غc�禡�{���X
			//
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button2;
	protected:



	protected:

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(235, 510);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 44);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Open Image";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(37, 24);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(533, 464);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(379, 510);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 44);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Noise";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(625, 576);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
		//�ŧiBitmap �x�s�}�Ҫ���
		Bitmap^ image1;

		//�ŧi���@BitmapData���A ��ܹ�����m
		Imaging::BitmapData ^ ImageData1;

		//�ŧi�Ϲ��ϰ�(�]�w����Ū���B���ץ����Ϲ��ϰ�)
		Rectangle rect;

		//�ŧi�@int�榡������
		IntPtr ptr, ResultPtr;

		//�ŧiByte�榡������
		Byte* p;
		Byte* R;
#pragma endregion
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {

		//new�@�ӷs��openFileDialog1�}���ɮ�
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		//�]�wFilter�A�ΥH���w�ϥΪ̶}�Ҫ��ɮ�
		openFileDialog1->Filter = "�I�}�� (*.bmp)| *.bmp| All files (*.*)| *.*";
		//�w�]�ɮצW�٬��ŭ�
		openFileDialog1->FileName = "";
		//�]�w���X��ܵ��������D�W��
		openFileDialog1->Title = "���J�v��";
		//�]�wFilter��ܼҦ�(�̷�Filter�ơA�p���ҿ��1��ܰ_�l�X�{�����I�}�ϡA���2���All filts)
	    openFileDialog1->FilterIndex = 1;


		//���X�ɮ׿�ܵ���(ShowDialog)�A�åB�p�G�ϥΪ��I���ɮסA�åB�ɮצW�ٶW�L0�Ӧr���A�h�P�_�O��True�A�i�J�B�z�{��
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0)
		{
			//�N������ɮ�Ū���åB�s��Image1
			image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));
			//�]�wrect�d��j�p
			rect = Rectangle(0, 0, image1->Width, image1->Height);
			//�N�v����ܦbpictureBox1
			pictureBox1->Image = image1;
		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		//�v���W�[���Q���T

		//�ŧiNoiseImage��BitMap^���A
		Bitmap^ NoiseImage;

		NoiseImage = gcnew Bitmap(image1->Width, image1->Height);
		//�ŧiNoiseImageData��BitmapData^���A�A��ܹ�����Ʀ�m
		Imaging::BitmapData^ NoiseImageData;
		//��w���B�z������m
		NoiseImageData = NoiseImage->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		//�Nint���Ы��VImage������ƪ��̫e����m
		ResultPtr = NoiseImageData->Scan0;
		//�]�w����
		R = (Byte*)((Void*)ResultPtr);

		//��w��ϱ��B�z������m
		ImageData1 = image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		//�Nint���Ы��V��Ϲ�����Ƴ̫e����m
		ptr = ImageData1->Scan0;
		//�]�w����
		p = (Byte*)((Void*)ptr);

		double mean = 0;//�����
		double std = 1;//�зǮt
		double u, v;//���ä����ƭ�
		double X;//�`�A���G�ƭ�

		//�s���Ҧ������I�A���ι����A�B�z�����ϰ�
		for (int y = 0; y < image1->Height; y++)
		{
			for (int x = 0; x < image1->Width; x++)
			{
				u = rand() / (double)RAND_MAX;//RAND_MAX=32767
				v = rand() / (double)RAND_MAX;

				X = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v) * std + mean;//M_PI=3.14159

				if (X > 2 || X < -2) 
				{
					if (X > 2) //���Q
					{
						R[0] = 255;
						R[1] = 255;
						R[2] = 255;
					}
					else if (X < -2)  //���­J��
					{
						R[0] = 0;
						R[1] = 0;
						R[2] = 0;
					}
				}
				else
				{
					//������Ϲ���
					R[0] = p[0];
					R[1] = p[1];
					R[2] = p[2];
				}

				R += 3;
				p += 3;
			}
		}

		//���깳����m
		image1->UnlockBits(ImageData1);
		NoiseImage->UnlockBits(NoiseImageData);
		//��ܦbPictureBox�W
		pictureBox1->Image = NoiseImage;
	}
};
}