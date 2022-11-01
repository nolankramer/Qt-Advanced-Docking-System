#ifndef AutoHideSideBarH
#define AutoHideSideBarH
/*******************************************************************************
** Qt Advanced Docking System
** Copyright (C) 2017 Uwe Kindler
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


//============================================================================
/// \file   AutoHideSideBar.h
/// \author Syarif Fakhri
/// \date   05.09.2022
/// \brief  Declaration of CAutoHideSideBar class
//============================================================================

//============================================================================
//                                   INCLUDES
//============================================================================
#include <QFrame>
#include "ads_globals.h"
#include "AutoHideTab.h"

class QXmlStreamWriter;

namespace ads
{
struct AutoHideSideBarPrivate;
class DockContainerWidgetPrivate;
class CDockContainerWidget;
class CAutoHideTab;
class CAutoHideDockContainer;
class CDockingStateReader;

/**
 * Side tab bar widget that is shown at the edges of a dock container.
 * The tab bar is only visible, if it contains visible content, that means if
 * it contains visible tabs. If it is empty or all tabs are hidden, then the
 * side bar is also hidden. As soon as one single tab becomes visible, this
 * tab bar will be shown.
 */
class ADS_EXPORT CAutoHideSideBar : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int sideBarLocation READ sideBarLocation)
    Q_PROPERTY(Qt::Orientation orientation READ orientation)

private:
    AutoHideSideBarPrivate* d; ///< private data (pimpl)
	friend struct AutoHideSideBarPrivate;
	friend class DockWidgetSideTab;
	friend DockContainerWidgetPrivate;

protected:
	virtual bool event(QEvent* e) override;
	virtual bool eventFilter(QObject *watched, QEvent *event) override;

	/**
	 * Saves the state into the given stream
	 */
	void saveState(QXmlStreamWriter& Stream) const;

	/**
	 * Inserts the given dock widget tab at the given position.
	 * An Index value of -1 appends the side tab at the end.
	 */
	void insertTab(int Index, CAutoHideTab* SideTab);

public:
    using Super = QFrame;

	/**
	 * Default Constructor
	 */
    CAutoHideSideBar(CDockContainerWidget* parent, SideBarLocation area);

	/**
	 * Virtual Destructor
	 */
	virtual ~CAutoHideSideBar();

	/**
	 * Removes the given DockWidgetSideTab from the tabbar
	 */
	void removeTab(CAutoHideTab* SideTab);

	/**
	 * Insert dock widget into the side bar.
	 * The function creates the auto hide dock container, inserts the
	 * auto hide tab
	 */
	CAutoHideDockContainer* insertDockWidget(int Index, CDockWidget* DockWidget);

	/**
	 * Returns orientation of side tab.
	 */
	Qt::Orientation orientation() const;

	/*
	 * get the side tab widget at position, returns nullptr if it's out of bounds
	 */
	CAutoHideTab* tabAt(int index) const;

	/*
	 * Gets the count of the tab widgets
	 */
	int tabCount() const;

	/**
	 * Getter for side tab bar area property
	 */
	SideBarLocation sideBarLocation() const;

Q_SIGNALS:
	void sideTabAutoHideToggleRequested();
};
} // namespace ads
//-----------------------------------------------------------------------------
#endif