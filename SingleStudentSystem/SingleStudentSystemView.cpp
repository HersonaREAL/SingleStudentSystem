
// SingleStudentSystemView.cpp: CSingleStudentSystemView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SingleStudentSystem.h"
#endif

#include "SingleStudentSystemDoc.h"
#include "SingleStudentSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSingleStudentSystemView

IMPLEMENT_DYNCREATE(CSingleStudentSystemView, CView)

BEGIN_MESSAGE_MAP(CSingleStudentSystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSingleStudentSystemView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FANGMATH, &CSingleStudentSystemView::OnFangmath)
	ON_COMMAND(ID_FANGCPP, &CSingleStudentSystemView::OnFangcpp)
	ON_COMMAND(ID_ZHEMATH, &CSingleStudentSystemView::OnZhemath)
	ON_COMMAND(ID_ZHECPP, &CSingleStudentSystemView::OnZhecpp)
END_MESSAGE_MAP()

// CSingleStudentSystemView 构造/析构

CSingleStudentSystemView::CSingleStudentSystemView() noexcept
{
	// TODO: 在此处添加构造代码

}

CSingleStudentSystemView::~CSingleStudentSystemView()
{
}

BOOL CSingleStudentSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSingleStudentSystemView 绘图

void CSingleStudentSystemView::OnDraw(CDC* /*pDC*/)
{
	CSingleStudentSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CSingleStudentSystemView 打印


void CSingleStudentSystemView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSingleStudentSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSingleStudentSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSingleStudentSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CSingleStudentSystemView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSingleStudentSystemView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSingleStudentSystemView 诊断

#ifdef _DEBUG
void CSingleStudentSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CSingleStudentSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSingleStudentSystemDoc* CSingleStudentSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSingleStudentSystemDoc)));
	return (CSingleStudentSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CSingleStudentSystemView 消息处理程序





void CSingleStudentSystemView::OnFangmath()
{
	// TODO: 在此添加命令处理程序代码
	if (theApp.HD->Next == NULL) {
		MessageBox("无数据,无法画图！");
		return;
	}

	int nMathScoreNum[] = { 0, 0, 0, 0, 0 };  // 高数各成绩段的人数的初 始值 
	List temp = theApp.HD->Next;
	while (temp != NULL) {
		if (atoi(temp->Stu.Math) < 60)//char*转化int
			nMathScoreNum[0]++;
		else if (atoi(temp->Stu.Math) >= 60 && atoi(temp->Stu.Math) < 70)
			nMathScoreNum[1]++;
		else if (atoi(temp->Stu.Math) >= 70 && atoi(temp->Stu.Math) < 80)
			nMathScoreNum[2]++;
		else if (atoi(temp->Stu.Math) >= 80 && atoi(temp->Stu.Math) < 90)
			nMathScoreNum[3]++;
		else if (atoi(temp->Stu.Math) >= 90 && atoi(temp->Stu.Math) <= 100)
			nMathScoreNum[4]++;

		temp = temp->Next;
	}

	CDC* pDC = this->GetDC();
	CRect rc;
	GetClientRect(rc);
	rc.DeflateRect(180, 40);
	pDC->FillSolidRect(&rc, RGB(255, 255, 255));//刷新画布

	int nSegHeight = rc.Height() / theApp.HD->ListNum;   // 计算每段的单位高度
	int nSegWidth = rc.Width() / 5;   // 计算每段的宽度
	COLORREF crSeg = RGB(76, 74, 72);//颜色
	CBrush brush1(HS_FDIAGONAL, crSeg);
	CBrush brush2(HS_BDIAGONAL, crSeg);
	CPen   pen(PS_INSIDEFRAME, 2, crSeg);
	CBrush* oldBrush = pDC->SelectObject(&brush1);   // 将brush1选入设备环境   
	CPen* oldPen = pDC->SelectObject(&pen);  // 将pen选 入设备环境 
	CRect rcSeg(rc);
	rcSeg.right = rcSeg.left + nSegWidth;   // 使每段的矩形宽度等于nSegWidth
	CString strSeg[] = { (CString)"<60", (CString)"60-70", (CString)"70-80", (CString)"80-90", (CString)">=90" };
	CRect rcStr;
	for (int i = 0; i < 5; i++)
	{  // 保证相邻的矩形填充样式不相同    
		if (i % 2)
			pDC->SelectObject(&brush2);
		else
			pDC->SelectObject(&brush1);
		rcSeg.top = rcSeg.bottom - nMathScoreNum[i] * nSegHeight - 2;  // 计算每段矩形的高度   
		pDC->Rectangle(rcSeg);
		if (nMathScoreNum[i] > 0)
		{
			CString str;
			str.Format((CString)"%d人", nMathScoreNum[i]);
			pDC->DrawText(str, rcSeg, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		rcStr = rcSeg;
		rcStr.top = rcStr.bottom + 2;
		rcStr.bottom += 20;
		pDC->DrawText(strSeg[i], rcStr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rcSeg.OffsetRect(nSegWidth, 0);  // 右移矩形   
	}
	pDC->SelectObject(oldBrush);  // 恢复原来的画刷属性   
	pDC->SelectObject(oldPen);    // 恢复原来的画笔属性 

	CDC* pControlDC = pDC;
	pControlDC->SelectStockObject(BLACK_BRUSH);//设置画刷
	CString str;
	pControlDC->TextOut(180, 200, "高数方形图");
}



void CSingleStudentSystemView::OnFangcpp()
{
	// TODO: 在此添加命令处理程序代码
	if (theApp.HD->Next == NULL) {
		MessageBox("无数据,无法画图！");
		return;
	}


	int nCPPScoreNum[] = { 0, 0, 0, 0, 0 };  // CPP各成绩段的人数的初 始值 
	List temp = theApp.HD->Next;
	while (temp != NULL) {
		if (atoi(temp->Stu.CPP) < 60)//char*转化int
			nCPPScoreNum[0]++;
		else if (atoi(temp->Stu.CPP) >= 60 && atoi(temp->Stu.CPP) < 70)
			nCPPScoreNum[1]++;
		else if (atoi(temp->Stu.CPP) >= 70 && atoi(temp->Stu.CPP) < 80)
			nCPPScoreNum[2]++;
		else if (atoi(temp->Stu.CPP) >= 80 && atoi(temp->Stu.CPP) < 90)
			nCPPScoreNum[3]++;
		else if (atoi(temp->Stu.CPP) >= 90 && atoi(temp->Stu.CPP) <= 100)
			nCPPScoreNum[4]++;

		temp = temp->Next;
	}

	CDC* pDC = this->GetDC();
	CRect rc;
	GetClientRect(rc);
	rc.DeflateRect(180, 40);
	pDC->FillSolidRect(&rc, RGB(255, 255, 255));//刷新画布

	int nSegHeight = rc.Height() / theApp.HD->ListNum;   // 计算每段的单位高度
	int nSegWidth = rc.Width() / 5;   // 计算每段的宽度
	COLORREF crSeg = RGB(76, 74, 72);//颜色
	CBrush brush1(HS_FDIAGONAL, crSeg);
	CBrush brush2(HS_BDIAGONAL, crSeg);
	CPen   pen(PS_INSIDEFRAME, 2, crSeg);
	CBrush* oldBrush = pDC->SelectObject(&brush1);   // 将brush1选入设备环境   
	CPen* oldPen = pDC->SelectObject(&pen);  // 将pen选 入设备环境 
	CRect rcSeg(rc);
	rcSeg.right = rcSeg.left + nSegWidth;   // 使每段的矩形宽度等于nSegWidth
	CString strSeg[] = { (CString)"<60", (CString)"60-70", (CString)"70-80", (CString)"80-90", (CString)">=90" };
	CRect rcStr;
	for (int i = 0; i < 5; i++)
	{  // 保证相邻的矩形填充样式不相同    
		if (i % 2)
			pDC->SelectObject(&brush2);
		else
			pDC->SelectObject(&brush1);
		rcSeg.top = rcSeg.bottom - nCPPScoreNum[i] * nSegHeight - 2;  // 计算每段矩形的高度   
		pDC->Rectangle(rcSeg);
		if (nCPPScoreNum[i] > 0)
		{
			CString str;
			str.Format((CString)"%d人", nCPPScoreNum[i]);
			pDC->DrawText(str, rcSeg, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		rcStr = rcSeg;
		rcStr.top = rcStr.bottom + 2;
		rcStr.bottom += 20;
		pDC->DrawText(strSeg[i], rcStr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rcSeg.OffsetRect(nSegWidth, 0);  // 右移矩形   
	}
	pDC->SelectObject(oldBrush);  // 恢复原来的画刷属性   
	pDC->SelectObject(oldPen);    // 恢复原来的画笔属性 

	CDC* pControlDC = pDC;
	pControlDC->SelectStockObject(BLACK_BRUSH);//设置画刷
	CString str;
	pControlDC->TextOut(180, 200, "C++方形图");
}


void CSingleStudentSystemView::OnZhemath()
{
	// TODO: 在此添加命令处理程序代码
	if (theApp.HD->Next == NULL) {
		MessageBox("无数据,无法画图！");
		return;
	}
	int nMathScoreNum[] = { 0, 0, 0, 0, 0 };//各成绩段人数
	List temp = theApp.HD->Next;
	while (temp != NULL) {
		if (atoi(temp->Stu.Math) < 60)//char*转化int
			nMathScoreNum[0]++;
		else if (atoi(temp->Stu.Math) >= 60 && atoi(temp->Stu.Math) < 70)
			nMathScoreNum[1]++;
		else if (atoi(temp->Stu.Math) >= 70 && atoi(temp->Stu.Math) < 80)
			nMathScoreNum[2]++;
		else if (atoi(temp->Stu.Math) >= 80 && atoi(temp->Stu.Math) < 90)
			nMathScoreNum[3]++;
		else if (atoi(temp->Stu.Math) >= 90 && atoi(temp->Stu.Math) <= 100)
			nMathScoreNum[4]++;
		
		temp = temp->Next;
	}

	CDC* pDC = this->GetDC();
	CDC* pControlDC = pDC;

	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(&rc, RGB(255, 255, 255));//刷新画布

	pControlDC->SelectStockObject(BLACK_BRUSH);//设置画刷
	CString str;
	CString strSeg[] = { (CString)"<60", (CString)"60-70", (CString)"70-80", (CString)"80-90", (CString)">=90" };
	pControlDC->MoveTo(180, 40);//画线的开始位置
	pControlDC->LineTo(180, 380);
	pControlDC->MoveTo(180, 380);//画线的开始位置
	pControlDC->LineTo(900, 380);
	pControlDC->MoveTo(180, 380);
	for (int i = 0; i < 5; i++)
	{
		pControlDC->SetPixel(0, 290, RGB(0, 0, 255));  //设置点的位置及颜色
		pControlDC->LineTo(i * 140 + 220, 380 - (380 * nMathScoreNum[i] / theApp.HD->ListNum));//画两点之间的线
		str.Format("%d人", nMathScoreNum[i]);
		pControlDC->TextOut(i * 140 + 220, 380 - (380 * nMathScoreNum[i] / theApp.HD->ListNum) - 20, str);//在线的上方输出文字
		pControlDC->TextOut(i * 140 + 220, 390, strSeg[i]);
	}

	pControlDC->TextOut(190, 100, "高数折线图");
}


void CSingleStudentSystemView::OnZhecpp()
{
	// TODO: 在此添加命令处理程序代码
	if (theApp.HD->Next == NULL) {
		MessageBox("无数据,无法画图！");
		return;
	}
	int nCPPScoreNum[] = { 0, 0, 0, 0, 0 };//各成绩段人数
	List temp = theApp.HD->Next;
	while (temp != NULL) {
		if (atoi(temp->Stu.CPP) < 60)//char*转化int
			nCPPScoreNum[0]++;
		else if (atoi(temp->Stu.CPP) >= 60 && atoi(temp->Stu.CPP) < 70)
			nCPPScoreNum[1]++;
		else if (atoi(temp->Stu.CPP) >= 70 && atoi(temp->Stu.CPP) < 80)
			nCPPScoreNum[2]++;
		else if (atoi(temp->Stu.CPP) >= 80 && atoi(temp->Stu.CPP) < 90)
			nCPPScoreNum[3]++;
		else if (atoi(temp->Stu.CPP) >= 90 && atoi(temp->Stu.CPP) <= 100)
			nCPPScoreNum[4]++;

		temp = temp->Next;
	}


	CDC* pDC = this->GetDC();
	CDC* pControlDC = pDC;

	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(&rc, RGB(255, 255, 255));//刷新画布

	pControlDC->SelectStockObject(BLACK_BRUSH);//设置画刷
	CString str;
	CString strSeg[] = { (CString)"<60", (CString)"60-70", (CString)"70-80", (CString)"80-90", (CString)">=90" };
	pControlDC->MoveTo(180, 40);//画线的开始位置
	pControlDC->LineTo(180, 380);
	pControlDC->MoveTo(180, 380);//画线的开始位置
	pControlDC->LineTo(900, 380);
	pControlDC->MoveTo(180, 380);
	for (int i = 0; i < 5; i++)
	{
		pControlDC->SetPixel(0, 290, RGB(0, 0, 255));  //设置点的位置及颜色
		pControlDC->LineTo(i * 140 + 220, 380 - (380 * nCPPScoreNum[i] / theApp.HD->ListNum));//画两点之间的线
		str.Format("%d人", nCPPScoreNum[i]);
		pControlDC->TextOut(i * 140 + 220, 380 - (380 * nCPPScoreNum[i] / theApp.HD->ListNum) - 20, str);//在线的上方输出文字
		pControlDC->TextOut(i * 140 + 220, 390, strSeg[i]);
	}

	pControlDC->TextOut(190, 100, "C++折线图");
}
