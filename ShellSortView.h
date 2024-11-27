
// ShellSortView.h : interface of the CShellSortView class
//

#pragma once


class CShellSortView : public CScrollView
{
protected: // create from serialization only
	CShellSortView() noexcept;
	DECLARE_DYNCREATE(CShellSortView)

// Attributes
public:
	CShellSortDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CShellSortView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString viewStr;
	afx_msg void OnDemo();
	void ShellSort(CString& str);
	void turnCString(vector<long long> data);
};

#ifndef _DEBUG  // debug version in ShellSortView.cpp
inline CShellSortDoc* CShellSortView::GetDocument() const
   { return reinterpret_cast<CShellSortDoc*>(m_pDocument); }
#endif

