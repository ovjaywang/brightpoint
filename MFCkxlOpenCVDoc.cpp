// MFCkxlOpenCVDoc.cpp : implementation of the CMFCkxlOpenCVDoc class
//

#include "stdafx.h"
#include "MFCkxlOpenCV.h"

#include "MFCkxlOpenCVDoc.h"
#include "OpenCVkxlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <fstream>
#include <iostream>
#include "dbscan.h"
#include<math.h>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVDoc

IMPLEMENT_DYNCREATE(CMFCkxlOpenCVDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCkxlOpenCVDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCkxlOpenCVDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVDoc construction/destruction

	//-----------��ʼ��-------------//
CMFCkxlOpenCVDoc::CMFCkxlOpenCVDoc()
{
	// TODO: add one-time construction code here
	m_pImage    = NULL;
	m_pImageSrc = NULL;
//	m_pImageGray = NULL;
	for (int i=0;i<20;i++)
	{
		pImage[i]=NULL;
	}
	pIm=0;
}

CMFCkxlOpenCVDoc::~CMFCkxlOpenCVDoc()
{
}

BOOL CMFCkxlOpenCVDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVDoc serialization

void CMFCkxlOpenCVDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVDoc diagnostics

#ifdef _DEBUG
void CMFCkxlOpenCVDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCkxlOpenCVDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVDoc commands


		//---------------��ͼ�� ��ʼ������---------------//
BOOL CMFCkxlOpenCVDoc::OnOpenDocument(LPCTSTR lpszPathName) //�и�СBUG
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	image_s = lpszPathName;
	// TODO: Add your specialized creation code here
	if(m_pImage != NULL)
	{
		cvReleaseImage(&m_pImage);
		cvReleaseImage(&m_pImageSrc);
	}
//	m_pImageGray=cvLoadImage(lpszPathName,0);

	m_pImage = cvLoadImage(lpszPathName, 1);
	m_pImageSrc = cvLoadImage(lpszPathName, 1);
	m_pImageFirst = cvLoadImage(lpszPathName,1);
	return TRUE;
}

					//--------------����ͼ��---------------//
BOOL CMFCkxlOpenCVDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	SaveImage(image_s);	
	return true;
	//	return CDocument::OnSaveDocument(lpszPathName);
}

bool CMFCkxlOpenCVDoc::SaveImage(CString path)
{
	if(m_pImage == NULL)
	{
		return false;
	}
	
	cvSaveImage(path, m_pImage);
	return true;
}


						//------------------------����----------------------//
bool CMFCkxlOpenCVDoc::Restore()
{
	pIm--;
	if (pIm<0)
	{	
		pIm++;
		return false;
	}else
	{
		cvReleaseImage(&m_pImage);
		m_pImage=cvCreateImage(cvGetSize(pImage[pIm]),pImage[pIm]->depth,pImage[pIm]->nChannels);
		cvCopy(pImage[pIm],m_pImage);
		
		cvReleaseImage(&m_pImageSrc);
		m_pImageSrc=cvCreateImage(cvGetSize(pImage[pIm]),pImage[pIm]->depth,pImage[pIm]->nChannels);
		cvCopy(pImage[pIm],m_pImageSrc);
		
		cvReleaseImage(&pImage[pIm]);
		return true;
	}
}


						//--------------------����---------------------//
void CMFCkxlOpenCVDoc::Backup()
{
	if (pImage[pIm]!=NULL)
	{
		cvReleaseImage(&pImage[pIm]);
	}
	pImage[pIm]=cvCreateImage(cvGetSize(m_pImage),m_pImage->depth,m_pImage->nChannels);
	cvCopy(m_pImage,pImage[pIm]);
	pIm++;
}

					//--------------------���¼���-------------------//
bool CMFCkxlOpenCVDoc::Reload()
{
	if (m_pImage!=NULL)
	{
		cvReleaseImage(&m_pImage);
	}
	
	m_pImage=cvCreateImage(cvGetSize(m_pImageFirst),m_pImageFirst->depth,m_pImageFirst->nChannels);
	cvCopy(m_pImageFirst,m_pImage);
	m_pImageSrc=cvCreateImage(cvGetSize(m_pImageFirst),m_pImageFirst->depth,m_pImageFirst->nChannels);
	cvCopy(m_pImageFirst,m_pImageSrc);

	for (int i=0;i<20;i++)
	{
		pImage[i]=NULL;
	}
	pIm=0;	

	return true;
}

						//----------------------�Ŵ�ͼ��---------------------//
bool CMFCkxlOpenCVDoc::zoom(double ratio)
{	
	Backup();
	if(ratio <= 0)
		return false;
	
	CvSize size;
	size.width  = int(m_pImageSrc->width  * ratio);
	size.height = int(m_pImageSrc->height * ratio);
	
	
	m_pImage = cvCreateImage(size, m_pImageSrc->depth, m_pImageSrc->nChannels);

	cvResize(m_pImageSrc, m_pImage);
	cvReleaseImage(&m_pImageSrc);

	m_pImageSrc=cvCreateImage(cvGetSize(m_pImage),m_pImage->depth,m_pImage->nChannels);
	cvCopy(m_pImage,m_pImageSrc);
	return true;
}
//���㷽��
double CMFCkxlOpenCVDoc::getFangcha(double aa[]){
	double avg = (aa[0] + aa[1] + aa[2]) / 3;
	double fangcha = (aa[0] - avg)*(aa[0] - avg) + (aa[1] - avg)*(aa[1] - avg) + (aa[2] - avg)*(aa[2] - avg);
	return sqrt(fangcha);
}
//�����ȡ��������Ԫ��
vector<Point2D> CMFCkxlOpenCVDoc::getThreeData(int mode, vector<Point2D> vt, int xy){ 
	//����vector ÿ��Ԫ��Ϊpoint2d�� ��С�̶�Ϊ3
	//mode 1=ǰ���� 9=������ xy 1��ʾȡx���� 2��ʾȡy����
	vector<Point2D> rs = vector<Point2D>();
	Point2D aa[8] = { vt[0], vt[1], vt[2], vt[3], vt[4], vt[5], vt[6], vt[7] };
	Point2D temp;
	int count = 8;
	for (int i = 1; i < count; i++)
	{
		if (xy == 1){
			for (int j = count - 1; j >= i; j--)
			{
				if (mode == 1){
					if (aa[j].GetX() < aa[j - 1].GetX())
					{
						temp = aa[j - 1];
						aa[j - 1]=aa[j];
						aa[j]=temp;
					}
				}
				else if (mode == 9){
					if (aa[j].GetX() > aa[j - 1].GetX())
					{
						temp = aa[j - 1];
						aa[j - 1]=aa[j];
						aa[j]=temp;
					}
				}
			}
		}
		else if (xy == 2){
			for (int j = count - 1; j >= i; j--)
			{
				if (mode == 1){
					if (aa[j].GetY() < aa[j - 1].GetY())
					{
						temp = aa[j - 1];
						aa[j - 1]=aa[j];
						aa[j]=temp;
					}
				}
				else if (mode == 9){
					if (aa[j].GetY() > aa[j - 1].GetY())
					{
						temp = aa[j - 1];
						aa[j - 1]=aa[j];
						aa[j]=temp;
					}
				}
			}
		}

	}
	rs.push_back(aa[0]);
	rs.push_back(aa[1]);
	rs.push_back(aa[2]);
	return rs;
}
ofstream ofs;
CvMemStorage * g_storage = NULL;
int clusterNum = 0;
	bool  CMFCkxlOpenCVDoc::fit_ellipse()
	{
		IplImage* m_pImageGray;
		m_pImageGray = cvCreateImage(cvGetSize(m_pImageSrc), m_pImageSrc->depth, 1);

		
		m_pCont = cvCreateImage(cvGetSize(m_pImage), m_pImage->depth, m_pImage->nChannels);
		cvCvtColor(m_pImageSrc, m_pImageGray, CV_BGRA2GRAY);

		IplImage* m_threImg;
		m_threImg = cvCreateImage(cvGetSize(m_pImageGray), m_pImageGray->depth, 1);
		//Backup();
		int bbb = LastOccurence((char*)(LPCTSTR)image_s, "\\");
		int last = image_s.Find(".");
		CString name= image_s.Mid(bbb + 1, last - bbb - 1) ;

		cvThreshold(m_pImageGray, m_threImg, 55, 255, CV_THRESH_BINARY);
		//cvCanny(m_pImage, pCannyImg, 50, 150, 3);   //50,150�ɱ䣬3���ɱ�
		cvSaveImage("C:\\Users\\Administrator\\Videos\\" + name + "_bianyuan.bmp", m_threImg);
		if (g_storage == NULL)
		{
			g_storage = cvCreateMemStorage(0);
		}
		vector<Point2D> lst = vector<Point2D>();

		CvSeq* contours = 0;//��ֵͼ���ҵ�������������CvSeq * contour��

		//CvBox2D32f box;
		CvPoint *PointArray;
		CvPoint2D32f *PointArray2D32f;
		
		cvFindContours(m_threImg, g_storage, &contours, sizeof(CvContour), 0, 2, cvPoint(0, 0));    //������
		ofs.open("C:\\Users\\Administrator\\Videos\\"+name+".txt", ios_base::trunc | ios_base::in);
		
		int No_=0;
		for (; contours; contours = contours->h_next){
			int i;
			int count = contours->total;//��������
			CvPoint2D32f center;
			CvSize size;

			/*�����������6������cvFitEllipse_32f��Ҫ��*/
			if (count<6)
			{
				continue;
			}
			//cvDrawContours(m_pCont, contours, CV_RGB(0, 255, 0), CV_RGB(0, 255, 0),0, 1, 8, cvPoint(0, 0));
			
			//�����ڴ���㼯
			PointArray = (CvPoint *)malloc(count*sizeof(CvPoint));
			PointArray2D32f = (CvPoint2D32f*)malloc(count*sizeof(CvPoint2D32f));

			//�����ڴ����Բ����
			//box = (CvBox2D32f *)malloc(sizeof(CvBox2D32f));

			//�õ��㼯���������ֵ�ý����
			cvCvtSeqToArray(contours, PointArray, CV_WHOLE_SEQ);

			//��CvPoint�㼯ת��ΪCvBox2D32f����
			for (i = 0; i<count; i++)
			{
				PointArray2D32f[i].x = (float)PointArray[i].x;
				PointArray2D32f[i].y = (float)PointArray[i].y;
			}
			CvBox2D C;
			C = cvFitEllipse2(contours);
			//��ϵ�ǰ����
			//cvFitEllipse(PointArray2D32f, count, C);
			cvEllipseBox(m_pCont, C, CV_RGB(0, 0, 0), 1, 8, 0);
			//ofs << "[" << C.center.x << "," << C.center.y << "] "<<endl;
			lst.push_back(Point2D(C.center.x, C.center.y));//�����ĵ����lst
			
			
			free(PointArray);
			free(PointArray2D32f);
		}
		//��lst�����趨��ֵ
		for (int i = 0; i<lst.size(); i++){
			lst[i].setCluster(0);
			lst[i].setClassed(false);
		}
		//dbscan�㷨�����ж��Ƿ�Ϊ���ĵ㡣������ID��
		double e= 4000;
		int minPts = 4;
		dbscan(lst, e, minPts);//
		clusterNum = getClusterNum(lst);//�����㷨������������
		ofs << "ClusterSize = " << lst.size()<<endl;
		ofs << "ClusterNUm =" << clusterNum << endl;
		CvFont font;
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0f, 1.0f, 0, 3, 8);//����ָ�� ���� ��� �߶� б�� ��ϸ �ʻ�����

		vector<vector<Point2D>> lsttmp = vector<vector<Point2D>>();//���༯��
		vector<Point2D> centerPts = vector<Point2D>();
		vector<Point2D> linePts = vector<Point2D>();
		for (int b = 0; b < clusterNum; b++) {
			lsttmp.push_back(vector<Point2D>());//�½�������ÿһ�������ж���
		}
		for (int j = 0; j <lst.size(); j++)
		{
			if (lst[j].getCluster() != 0){
				lsttmp[lst[j].getCluster() - 1].push_back(lst[j]);//��ÿһ���ؼ���������Լ���ŵ�vector��
			}
			else{
				linePts.push_back(lst[j]);
			}
		}
		vector<vector<Point2D>>::iterator iter;
		int k = 0;
		for (iter = lsttmp.begin(); iter != lsttmp.end();)
		{
			k++;
			if ((*iter).size() != 8)
			{
				iter = lsttmp.erase(iter);
				clusterNum--;
			}
			else{
				Point2D centerPoint = getCenterPoint((*iter));
				centerPoint.setCluster(k);
				centerPts.push_back(centerPoint);
				++iter;
			}
		}
		getAllCtrlPointCoor(lsttmp, centerPts);

		cvSaveImage("C:\\Users\\Administrator\\Videos\\" + name + ".bmp", m_pCont);
		//cvZero(m_pImageGray);

//		cvCopy(m_pCont, m_pImageSrc);
		cvCopy(m_pCont, m_pImage);
		cvCopy(m_pCont, m_pImageSrc);
		cvReleaseImage(&m_pImageGray);
		cvReleaseImage(&m_threImg);
		cvReleaseImage(&(m_pCont));
		cvReleaseMemStorage(&g_storage);
		ofs.flush();
		ofs.close();
		return true;
	}
	void CMFCkxlOpenCVDoc::getAllCtrlPointCoor(vector<vector<Point2D>> lsttmp, vector<Point2D> centerPts)
	{//�����lsttmp�ǽ�ÿ���ؼ�������Լ��ľ����� ��������Ӧ��7�飬ÿ��8���㣩 
	 //ͼ���������5�����ϵİб��!!!!Ӳ��Ҫ��
		vector<vector<Point2D>> lstthreepoint = vector<vector<Point2D>>();
		vector<vector<Point2D>> lstthreepoint_3or4 = vector<vector<Point2D>>();
		bool is1Geted = false, is2Geted = false, is3Geted = false, is4Geted = false, is5Geted = false, is6Geted = false, is7Geted = false;//��ʼ���Ƿ�õ���Щ��
		bool is5Seperated = false;//5�Ƿ����
		int group13=0, group2=0, group23=0, group4 = 0;//�����б�ʽ��õĵ�
		int ptGeted = 0;
		int rs1, rs2, rs3, rs4, rs5, rs6, rs7 = 0;
		//vector<Point2D> set1 = vector<Point2D>();
		//vector<Point2D> set2 = vector<Point2D>();
		//vector<Point2D> set3 = vector<Point2D>();
		//vector<Point2D> set4 = vector<Point2D>(); 
		vector<Point2D> set34 = vector<Point2D>();
		//vector<Point2D> set5 = vector<Point2D>();
		//vector<Point2D> set6 = vector<Point2D>();
		//vector<Point2D> set7 = vector<Point2D>();
		CvFont font;
		int first_or_last,x_or_y;
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5f, 0.5f, 0, 1, 8);//����ָ�� ���� ��� �߶� б�� ��ϸ �ʻ�����
		//���б�y����������
		for (int b = 0; b < clusterNum; b++) {//��clusterNum������
			if (lsttmp[b].size() == 8){
				first_or_last = 1;
				x_or_y = 2;
				//ofs << "���ģʽ�� " << first_or_last << " ѡ�������ǣ� " << x_or_y << endl;
				vector<Point2D> threePts = getThreeData(first_or_last, lsttmp[b], x_or_y);//����ĳ�ַ�ʽ�µ�������ֵ�ķ���
				threePts[0].setCluster(b+1);
				lstthreepoint.push_back(threePts);//��ÿһ�������Ԫ������vector Ԫ�ع̶���СΪ3
			}
		}
		//�б��4��(����6)����ֻ��һ���㣬��֮�б��
		ofs << "RealSize �� " << lstthreepoint.size()<<endl<<endl;
		if(lstthreepoint.size() < 5)	return;
		int G_No = 0;
		for (int pp = 0; pp < lstthreepoint.size(); pp++){
			int x_first = getKeyCtrlNum(lstthreepoint[pp], 1, 2);
			if (x_first == 4 ){
				group4++;
				G_No = pp;
			}
		}
		if (group4 == 1){
			is6Geted = true;
			ptGeted += 1;
			ofs << "�ҵ��� 4 (���� 6)" << endl;
			rs6 = lstthreepoint[G_No][0].getCluster();
			ofs << "Point6��Ӧ���Ϊ��" << rs6<<endl;
			//for (int j = 0; j < 8;j++){
			//	Point2D ppt = Point2D(lsttmp[lstthreepoint[G_No][0].getCluster()][j].GetX(), lsttmp[lstthreepoint[G_No][0].getCluster()][j].GetY());
			//	ppt.setCluster(6);
			//	set6.push_back(ppt);
			//	//cvPutText(m_pCont, "6", cvPoint(ppt.GetX()- 5,ppt.GetY() + 3), &font, CV_RGB(255, 0, 0));
			//}
			center6 = centerPts[lstthreepoint[G_No][0].getCluster()-1];
			cvPutText(m_pCont, "6", cvPoint(center6.GetX() - 5, center6.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
		}
		else if (group4 == 0){
			ofs << "��4����ͼ���� (���� 6)" << endl;
		}
		else{
			ofs << "���� ,����1��������4 (����6)" << endl;
		}

		ofs << endl;
		lstthreepoint.clear();
		//�ڵ�2�ַ�ʽ��3��--x��ǰ3��
		for (int b = 0; b < clusterNum; b++) {//��clusterNum������
			if (lsttmp[b].size() == 8){
				vector<Point2D> threePts = getThreeData(1, lsttmp[b], 1);//����ĳ��������
				threePts[0].setCluster(b+1);
				lstthreepoint.push_back(threePts);//��ÿһ�������Ԫ������vector Ԫ�ع̶���СΪ3
			}
		}
		//�б��2��
		vector<int> find34 = vector<int>();
		double group34inlst = 0 ;
		for (int pp = 0; pp < lstthreepoint.size(); pp++){
			int x_first = getKeyCtrlNum(lstthreepoint[pp], 1, 1);
			if (x_first == 2){
				find34.push_back(pp);
				group2++;
			}
		}
		if (group2 == 2){
			is3Geted = true;
			is4Geted = true;
			ptGeted += 2;
			//�ҵ�2����������°�3 4 ��ͼ�б�ע
			if (lstthreepoint[find34[0]][0].GetX()<lstthreepoint[find34[1]][0].GetX()){
				rs3 = lstthreepoint[find34[0]][0].getCluster();
				rs4 = lstthreepoint[find34[1]][0].getCluster();
				//for (int j = 0; j < 8; j++){
				//	Point2D pt =Point2D(lsttmp[lstthreepoint[find34[0]][0].getCluster()][j].GetX(), lsttmp[lstthreepoint[find34[0]][0].getCluster()][j].GetY());
				//	pt.setCluster(3);
				//	set3.push_back(pt);//-5 +3Ϊ�˵�����ʶ���ֵ�λ��	
				//	//cvPutText(m_pCont, "3", cvPoint(pt.GetX() - 5,pt.GetY() + 3), &font, CV_RGB(255, 0, 0));
				//}
				center3 = centerPts[rs3-1];//��Ǿ���3
				cvPutText(m_pCont, "3", cvPoint(center3.GetX() - 5, center3.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��3
				//for (int j = 0; j < 8; j++){
				//	Point2D pt = Point2D(lsttmp[lstthreepoint[find34[1]][0].getCluster()][j].GetX(), lsttmp[lstthreepoint[find34[1]][0].getCluster()][j].GetY());
				//	pt.setCluster(4);
				//	set4.push_back(pt);
				//	//cvPutText(m_pCont, "4", cvPoint(pt.GetX() - 5,pt.GetY() + 3), &font, CV_RGB(255, 0, 0));
				//}
				center4 = centerPts[rs4 - 1];//��Ǿ���4
				cvPutText(m_pCont, "4", cvPoint(center4.GetX() - 5, center4.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
			}
			else{
				rs4 = lstthreepoint[find34[0]][0].getCluster();
				rs3 = lstthreepoint[find34[1]][0].getCluster();
				//for (int j = 0; j < 8; j++){
				//	Point2D pt = Point2D(lsttmp[lstthreepoint[find34[0]][0].getCluster()][j].GetX(), lsttmp[lstthreepoint[find34[0]][0].getCluster()][j].GetY());
				//	pt.setCluster(4);
				//	set4.push_back(pt);
				//	//cvPutText(m_pCont, "4", cvPoint(pt.GetX() - 5,pt.GetY()+ 3), &font, CV_RGB(255, 0, 0));
				//}
				center4 = centerPts[rs4 - 1];
				cvPutText(m_pCont, "4", cvPoint(center4.GetX() - 5, center4.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1

				//for (int j = 0; j < 8; j++){
				//	Point2D pt = Point2D(lsttmp[lstthreepoint[find34[1]][0].getCluster()][j].GetX(), lsttmp[lstthreepoint[find34[1]][0].getCluster()][j].GetY());
				//	pt.setCluster(3);
				//	set3.push_back(pt);
				//	//cvPutText(m_pCont, "3", cvPoint(pt.GetX()- 5,pt.GetY()+ 3), &font, CV_RGB(255, 0, 0));
				//}
				center3 = centerPts[rs3-1];
				cvPutText(m_pCont, "3", cvPoint(center3.GetX() - 5, center3.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
			}
			ofs << "�������Ӧlst���Ϊ��" << rs3 << endl;
			ofs << "�������Ӧlst���Ϊ��" << rs4 << endl;
			ofs << "�ҵ�ȫ����2(������ 34)" << endl;
		}
		else if (group2 == 1){
				ofs << "Found 1 pt in Group 2 (include34)" << endl;
				for (int j = 0; j < 8; j++){
					Point2D pt = Point2D(lsttmp[lstthreepoint[find34[0]][0].getCluster()][j].GetX(), lsttmp[lstthreepoint[find34[0]][0].getCluster()][j].GetY());
					pt.setCluster(lstthreepoint[find34[0]][0].getCluster());
					set34.push_back(pt);
				}
				//group34inlst = lstthreepoint[find34[0]][0].getCluster();
		}
		else if (group2 == 0){
			ofs << "Not found any in Group2 (include34)" << endl;
		}
		else{
			ofs << "Error ,More than 2 in Group 2 (include34)" << endl;
		}
		ofs << endl;
		
		lstthreepoint.clear();
		//�۵�3�ַ�ʽ��3��--y���3��ͬʱx���3�����ҳ�Group3��5��
		for (int b = 0; b < clusterNum; b++) {//��clusterNum������
			if (lsttmp[b].size() == 8){
				vector<Point2D> threePts = getThreeData(9, lsttmp[b], 2);//��23��
				threePts[0].setCluster(b+1);
				lstthreepoint.push_back(threePts);//��ÿһ�������Ԫ������vector Ԫ�ع̶���СΪ3
			}
		}
		//�б��23��
		int is5Group = 0;
		int tmp5Group = 0;
		for (int pp = 0; pp < lstthreepoint.size(); pp++){
			int x_first = getKeyCtrlNum(lstthreepoint[pp], 9, 2);
			if (x_first == 23){//��23������13��-5����
				vector<vector<Point2D>> pts5 = vector<vector<Point2D>>();
				group23++;
				vector<Point2D> threePts = getThreeData(9, lsttmp[lstthreepoint[pp][0].getCluster()-1], 1);//����ĳ��������,��3&x
				double abc[] = { threePts[0].GetX(), threePts[1].GetX(), threePts[2].GetX() };
				double fc=getFangcha(abc);
				ofs << "When get Group2 3 ��FC is " << fc << endl;
				if (fc > 12){
					is5Group++;
					tmp5Group = pp;//��ǵ�5����ʱ���
				}
			}
		}

		//�ҳ�5�ľ����б�
		if (is5Group == 1){
			ofs << "�ҵ��� 3��(����5)" << endl;
			//rs5 = lstthreepoint[tmp5Group][0].getCluster();
			rs5 = lstthreepoint[tmp5Group][0].getCluster();
			ofs << "Point5��Ӧ���Ϊ��" << rs5 << endl;
			center5 = centerPts[tmp5Group];
			cvPutText(m_pCont, "5" , cvPoint(center5.GetX() - 5,center5.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
			is5Geted = true;
		}
		else if (is5Group == 0){
			is5Geted = false;
			ofs << "�� 3 (����5) ����ͼ����"<<endl;
		}
		else {
			ofs << "���� ,����׼ȷ�ҵ���5"<<endl;
		}
		if (group23 == 3){
			ofs << "�ҵ���2����3���е�(������ 34 5)" << endl;
			is3Geted = true;
			is4Geted = true;
			is5Geted = true;
		}
		else if (group23 >0 && group23<3){
			ofs << "����2&��3�ҵ�" << group23 << "���� (������34 5)" << endl;
			//����Ӵ���
		}
		else if (group23 == 0){
			ofs << "δ�����κ���2����3��������345��" << endl;
		}
		else{
			ofs << "Error ,More than 3 in Group 23(include 34 5)" << endl;
		}
		//��ֻ��һ�����ʱ�� �б�2��������
		if (group2 == 1){

			if (is5Geted){
				if (set34[0].GetX()<lsttmp[lstthreepoint[tmp5Group][0].getCluster()][0].GetX()){//�����ҳ�һ��x������5����������
					rs3 = set34[0].getCluster();
					is3Geted = true;
					is4Geted = false;
					ofs << "�������Ӧlst���Ϊ��" << rs3 << endl;
					//for (int j = 0; j < 8; j++){
					//	Point2D pt = Point2D(set34[j].GetX(), set34[j].GetY());
					//	pt.setCluster(3);
					//	set3.push_back(pt);
					//	//cvPutText(m_pCont, "3", cvPoint(pt.GetX() - 5,pt.GetY() + 3), &font, CV_RGB(255, 0, 0));
					//}center3 = centerPts[rs3-1];
					center3 = centerPts[rs3 -1];
					cvPutText(m_pCont, "3", cvPoint(center3.GetX() - 5, center3.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
				}
				else{
					rs4 = set34[0].getCluster();
					ofs << "Point4��Ӧ�����Ϊ��" << rs4 << endl;
					is4Geted = true;
					is3Geted = false;
					//for (int j = 0; j < 8; j++){
					//	Point2D pt = Point2D(set34[j].GetX(), set34[j].GetY());
					//	pt.setCluster(4);
					//	set4.push_back(pt);
					//	//cvPutText(m_pCont, "4", cvPoint(pt.GetX()- 5,pt.GetY() + 3), &font, CV_RGB(255, 0, 0));
					//}
					center4 = centerPts[rs4 -1];
					cvPutText(m_pCont, "4", cvPoint(center4.GetX() - 5, center4.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1

				}
			}
		}
		ofs << endl;
		lstthreepoint.clear();
		vector<Point2D> find127 = vector<Point2D>();
		//�ܵ�4�ַ�ʽ��3��--x���ǰ3��
		for (int b = 0; b < clusterNum; b++) {//��clusterNum������
			if (lsttmp[b].size() == 8){
				vector<Point2D> threePts = getThreeData(9 , lsttmp[b] , 1);//����ĳ��������
				threePts[0].setCluster(b+1);
				lstthreepoint.push_back(threePts);//��ÿһ�������Ԫ������vector Ԫ�ع̶���СΪ3
			}
		}
		//�б��13��
		for (int pp = 0; pp < lstthreepoint.size(); pp++){
			int x_first = getKeyCtrlNum(lstthreepoint[pp], 9, 1);
			if (x_first == 13 && tmp5Group!= pp){
				group13++;
				find127.push_back(centerPts[lstthreepoint[pp][0].getCluster()-1]);//����Ԫ������ļ������� Ϊ������Gropu3(����5)
			}
		}
		if (group13 == 3){
			is1Geted = true;
			is2Geted = true;
			is7Geted = true;
			Point2D pt7 = find127[0];
			int loc7 =0 ;
			for (int ttt = 1; ttt < 3; ttt++){
				if (pt7.GetY() < find127[ttt].GetY()){
					pt7 = find127[ttt];
					loc7 = ttt;
				}
			}
			rs7 = find127[loc7].getCluster();
			ofs << "�������Ӧlst���Ϊ��" << rs7 << endl;
			Point2D center7 = centerPts[find127[loc7].getCluster()-1];
			cvPutText(m_pCont, "7", cvPoint(center7.GetX() - 5, center7.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1

			vector<Point2D> pt12 = vector<Point2D>();
			for (int j = 0; j < find127.size(); j++){
				if (find127[j].getCluster() != rs7){
					pt12.push_back(find127[j]);//�ų�����7 ��12�������
				}
			}
			rs1 = pt12[0].getCluster()-1;
			rs2 = pt12[1].getCluster()-1;
			//�жϵ�12����
			if (pt12[0].GetX() < pt12[1].GetX()){
				cvPutText(m_pCont, "1", cvPoint(centerPts[rs1].GetX() - 5, centerPts[rs1].GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
				cvPutText(m_pCont, "2", cvPoint(centerPts[rs2].GetX() - 5, centerPts[rs2].GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��2

			}
			else{
				cvPutText(m_pCont, "2", cvPoint(centerPts[rs1].GetX() - 5, centerPts[rs1].GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
				cvPutText(m_pCont, "1", cvPoint(centerPts[rs2].GetX() - 5, centerPts[rs2].GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1

			}
			ofs << "���˵�7�����ڴ��ڵ�����У�";
			for (int jj = 0; jj < pt12.size(); jj++){
				ofs << pt12[jj].getCluster() << " ";
			}
			ofs << endl;
			is1Geted = true;
			is2Geted = true;
			is5Geted = true;
			is7Geted = true;
		}
		//��1 3 ����4����
		else if (group13 >0&&group13<3){
			if (is5Geted){
				ofs << "����1�ҵ� " << group13<< " ����(���� 127)" << endl;
			for (int i = 0; i < find127.size(); i++)
				{
					if (find127[i].GetY() > center5.GetY()){
						center7 = find127[i];
						center7.setCluster(7);
						cvPutText(m_pCont, "7", cvPoint(center7.GetX() - 5, center7.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
					}
					else{
						if (find127[i].GetX() < center4.GetX()){
							
							center1 = find127[i];
							cvPutText(m_pCont, "1", cvPoint(center1.GetX() - 5, center1.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
						}
						else{
							center2 = find127[i];
							cvPutText(m_pCont, "2", cvPoint(center2.GetX() - 5, center2.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
						}
					}
				}
			}
			//else if (group13 == 3){//������û�ҵ������127����
			//	ofs << "�ҵ���1���еĵ� (���� 127)" << endl;
			//	is1Geted = true;
			//	is2Geted = true;
			//	is7Geted = true;
			//}
			else {
				ofs << "����1�ҵ� "<<group13 <<" ����(���� 127)" << endl;
			}
		}
		else if (group13 == 0){
			ofs << "��1 3 һ����Ҳû�� (���� 127 5)" << endl;
		}
		else{
			ofs << "���� ,��1 3����4���� (���� 127 5)" << endl;
		}
		if (is1Geted == true){
			if (group2 == 1){
				double tmp_mean_34 = 0.0;
				double tmp_mean_1 = 0.0;
				for (int i = 0; i < 8; i++)
				{
					tmp_mean_34 += set34[i].GetX();
					//tmp_mean_1 += set1[i].GetX();
				}
				tmp_mean_1 = center1.GetX();
				if (tmp_mean_34 < tmp_mean_1){
					center3 = getCenterPoint(set34);
					cvPutText(m_pCont, "3", cvPoint(center3.GetX() - 5, center3.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
					is3Geted = true;
				}
				else{
					center4 = getCenterPoint(set34);
					cvPutText(m_pCont, "4", cvPoint(center4.GetX() - 5, center4.GetY() + 3), &font, CV_RGB(255, 0, 0));//��ӡ��1
					is4Geted = true;
				}
			}
		}
	}
	Point2D CMFCkxlOpenCVDoc::getCenterPoint(vector<Point2D> vt){
		double min_X=999999.0, min_Y=999999.0, max_X=-1.0, max_Y=-1.0;
		for (int i = 0; i < vt.size(); i++)
		{
			if (min_X>vt[i].GetX()){
				min_X = vt[i].GetX();
			}
			if (min_Y > vt[i].GetY()){
				min_Y = vt[i].GetY();
			}
			if (max_X < vt[i].GetX()){
				max_X = vt[i].GetX();
			}
			if (max_Y < vt[i].GetY()){
				max_Y = vt[i].GetY();
			}
		}
		Point2D ppt = Point2D((min_X + max_X) / 2, (min_Y + max_Y) / 2);
		int index = -1;
		double length = 9999999.0;
		for (int i = 0; i < vt.size(); i++)
		{
			double length_tmp = sqrt((vt[i].GetX() - ppt.GetX())*(vt[i].GetX() - ppt.GetX()) + (vt[i].GetY() - ppt.GetY())*(vt[i].GetY() - ppt.GetY()));
			if (length_tmp < length){
				length = length_tmp;
				index = i;
			}
		}
		return vt[index];
	}
	//�ж����������͵ĵ�
int CMFCkxlOpenCVDoc::getKeyCtrlNum(vector<Point2D> vt, int mode, int xy){		//���vt��ĳ�ַ�ʽѡ����������
	if (vt.size() == 0){
		return 0;
	}
	if (xy == 1){
			double  aa[] = { vt[0].GetX(), vt[1].GetX(), vt[2].GetX() };
			double fangcha = getFangcha(aa);
			if (fangcha > 9 && mode == 1 ){
				return 2;
			}
			if (fangcha> 9 && mode == 9 ){//�����
				return 13;
			}

	}
	if (xy == 2) {
				double aa[] = { vt[0].GetY(), vt[1].GetY(), vt[2].GetY() };
				double fangcha=getFangcha(aa);
				//ofs << "fangcha : " << fangcha<<endl;
				if (fangcha > 13){
					if (mode == 1){
						return 4;
					}
					else if (mode == 9){
						return 23;
					}
				}
			
		}
		return 0;
	}
       //--------------------��תͼ��------------------------//
bool CMFCkxlOpenCVDoc::Flip(int flip_mode)
{
	Backup();
	if (m_pImageSrc==NULL)
	return false;
	else{
		//cvFlip(m_pImageSrc, m_pImageSrc, flip_mode);
		cvFlip(m_pImage, m_pImage, flip_mode);
		return true;
	}
}

                       //---------------------ת��---------------------//
bool CMFCkxlOpenCVDoc::Rotate(int angle)
{
	Backup();
	IplImage *dst = 0;
	if (angle==90||angle==-90)
	{
		CvSize size;
		size.width = (m_pImage)->height;
		size.height = (m_pImage)->width;
	
		dst = cvCreateImage(size, (m_pImage)->depth, (m_pImage)->nChannels);
		cvTranspose(m_pImage, dst);
//		cvReleaseImage(&(*imgSrc));
		m_pImage = dst;
		int f = (angle == 90)? 1 : 0;
		cvFlip(m_pImage, m_pImage, f);
		m_pImageSrc = cvCreateImage(size, (m_pImage)->depth, (m_pImage)->nChannels);
		cvCopy(m_pImage,m_pImageSrc);
		return true;
	}
	else 
		return false;
}


  

						//-------------------�ҶȻ�-------------------------//
bool CMFCkxlOpenCVDoc::Gray()
{
	Backup();
	if (m_pImageSrc==NULL)
		return false;
	else{
	/*	m_pImage=cvCreateImage(cvGetSize(m_pImageGray),m_pImageGray->depth,m_pImageGray->nChannels);
		cvCopy(m_pImageGray,m_pImage);
		return true;
		*/
		IplImage* m_pImageGray;
		m_pImageGray=cvCreateImage(cvGetSize(m_pImageSrc),m_pImageSrc->depth,1);
		cvCvtColor(m_pImageSrc,m_pImageGray,CV_BGRA2GRAY);
		m_pImage=cvCreateImage(cvGetSize(m_pImageGray),IPL_DEPTH_8U,3);
		cvCvtColor(m_pImageGray,m_pImage,CV_GRAY2RGB);
		m_pImageSrc=cvCreateImage(cvGetSize(m_pImageGray),IPL_DEPTH_8U,3);
		cvCopy(m_pImage,m_pImageSrc);
		return true;
	}
}

						//-------------------��ֵ�ָ�-------------------------//
bool CMFCkxlOpenCVDoc::CountCut()
{
	Backup();
	cvThreshold(m_pImage, m_pImage, 100, 255, CV_THRESH_BINARY );
	cvThreshold(m_pImageSrc, m_pImageSrc, 100, 255, CV_THRESH_BINARY );
	return true;
	
}




int CMFCkxlOpenCVDoc::LastOccurence(char *szStr, char *szSub) {
	int nSrcLen = strlen(szStr);
	int nSubLen = strlen(szSub);

	char *pch = szStr + (nSrcLen - nSubLen);
	int c = nSrcLen - nSubLen;
	while (pch > szStr) {
		if (strncmp(pch, szSub, nSubLen) == 0){
			return c;
		}		
		pch--;
		c--;
	}
	return 0;
}
