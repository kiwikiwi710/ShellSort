
// ShellSortView.cpp : implementation of the CShellSortView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ShellSort.h"
#endif

#include "ShellSortDoc.h"
#include "ShellSortView.h"
#include "CTest.h"
#include "sstream"
#include "vector"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShellSortView

IMPLEMENT_DYNCREATE(CShellSortView, CScrollView)

BEGIN_MESSAGE_MAP(CShellSortView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_DEMO, &CShellSortView::OnDemo)
END_MESSAGE_MAP()

// CShellSortView construction/destruction

CShellSortView::CShellSortView() noexcept
{
	// TODO: add construction code here

}

CShellSortView::~CShellSortView()
{
}

BOOL CShellSortView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CShellSortView drawing

void CShellSortView::OnDraw(CDC* pDC)
{
	CShellSortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CFont aFont;
	aFont.CreateFont(40, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Times New Roman");
	pDC->SelectObject(&aFont);

	if (pDoc->m_output.size() > 0)
		for (int i = 0; i < (pDoc->m_output.size()); i++)
			pDC->TextOut(0, i * 50, pDoc->m_output[i]);
}

void CShellSortView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 50000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CShellSortView printing

BOOL CShellSortView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CShellSortView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CShellSortView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CShellSortView diagnostics

#ifdef _DEBUG
void CShellSortView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CShellSortView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CShellSortDoc* CShellSortView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShellSortDoc)));
	return (CShellSortDoc*)m_pDocument;
}
#endif //_DEBUG


// CShellSortView message handlers


void CShellSortView::OnDemo()
{
	// TODO: Add your command handler code here
	CShellSortDoc* pDoc = GetDocument();
	CTest aDiag;
	CClientDC aDC(this);
	if (aDiag.DoModal() == IDOK) {
		pDoc->m_output.clear();
		viewStr = aDiag.diagStr;
		//pDoc->m_output.push_back(viewStr);
		ShellSort(viewStr);
		pDoc->UpdateAllViews(NULL);

	}
}


void CShellSortView::ShellSort(CString& str)
{
	// TODO: Add your implementation code here.
	string str2 = CT2A(str.GetBuffer());
	string s1;
	CShellSortDoc* pDoc = GetDocument();
	long long n;
	stringstream s, s2;
	s << str2;
	vector<long long> data,data2;
	while (getline(s, s1, ',')) {
		s2 << s1;
		s2 >> n;
		data.push_back(n);
		s2.clear();
	}

	int h = 1;
	do {
		h = 3 * h + 1;
	} while (h <= data.size());

	do {
		h /= 3;
		CString c;
		c.Format(L"h = %d", h);
		pDoc->m_output.push_back(c);
		pDoc->m_output.push_back(L"排序前的數列:");
		int w = data.size() % h == 0 ? data.size() / h : data.size() / h + 1;
		int index=0;
		for (int j = 0; j < w; j++) {

			for (int i=0; (i < h) && index < (data.size());i++) {
				data2.push_back(data[index]);
				index++;
			}
			turnCString(data2);
			data2.clear();
		}

		for (int k = h + 1; k < data.size(); k++)
		{
			long temp = data[k];
			int j = k;

			while (j - h >= 0 && data[j - h] > temp)
			{
				data[j] = data[j - h];
				j -= h;
			}

			if (data[j] != temp)
			{
				data[j] = temp;
			}	
		}
		data2.clear(); 
		index = 0;
		pDoc->m_output.push_back(L"排序後的數列:");
		for (int j = 0; j < w; j++) {
			for (int i=0; (i < h) && index < (data.size()); i++) {
				data2.push_back(data[index]);
				index++;
			}
			turnCString(data2);
			data2.clear();
		}
	} while (h > 1);
}


void CShellSortView::turnCString(vector<long long> data)
{
	// TODO: Add your implementation code here.
	CShellSortDoc* pDoc = GetDocument();
	CString str, tmp;
	str.Format(L"%lli", data[0]);
	for (int i = 1; i < data.size(); i++)
	{
		str += L",";
		tmp.Format(L"%lli", data[i]);
		str += tmp;
	}
	pDoc->m_output.push_back(str);
}
