
// SingleStudentSystemView.h: CSingleStudentSystemView 类的接口
//

#pragma once


class CSingleStudentSystemView : public CView
{
protected: // 仅从序列化创建
	CSingleStudentSystemView() noexcept;
	DECLARE_DYNCREATE(CSingleStudentSystemView)

// 特性
public:
	CSingleStudentSystemDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSingleStudentSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFang();
	afx_msg void OnZhe();
	afx_msg void OnFangmath();
	afx_msg void OnFangcpp();
	afx_msg void OnZhemath();
	afx_msg void OnZhecpp();
};

#ifndef _DEBUG  // SingleStudentSystemView.cpp 中的调试版本
inline CSingleStudentSystemDoc* CSingleStudentSystemView::GetDocument() const
   { return reinterpret_cast<CSingleStudentSystemDoc*>(m_pDocument); }
#endif

