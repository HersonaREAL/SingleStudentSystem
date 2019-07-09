
// SingleStudentSystemDoc.cpp: CSingleStudentSystemDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SingleStudentSystem.h"
#endif

#include "SingleStudentSystemDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSingleStudentSystemDoc

IMPLEMENT_DYNCREATE(CSingleStudentSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CSingleStudentSystemDoc, CDocument)
END_MESSAGE_MAP()


// CSingleStudentSystemDoc 构造/析构

CSingleStudentSystemDoc::CSingleStudentSystemDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CSingleStudentSystemDoc::~CSingleStudentSystemDoc()
{
}

BOOL CSingleStudentSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	SetTitle("成绩分析-蒋耀聪 网络184 1806200016");
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSingleStudentSystemDoc 序列化

void CSingleStudentSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSingleStudentSystemDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CSingleStudentSystemDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSingleStudentSystemDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSingleStudentSystemDoc 诊断

#ifdef _DEBUG
void CSingleStudentSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSingleStudentSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSingleStudentSystemDoc 命令
