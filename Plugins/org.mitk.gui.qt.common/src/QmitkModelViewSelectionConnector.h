/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical Image Computing.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef QMITKMODELVIEWSELECTIONCONNECTOR_H
#define QMITKMODELVIEWSELECTIONCONNECTOR_H

#include <org_mitk_gui_qt_common_Export.h>

// qt widgets module
#include <QmitkAbstractDataStorageModel.h>

 // qt
#include <QAbstractItemView>

/*
* @brief The 'QmitkModelViewSelectionConnector' is used to handle the selections of a model-view-pair.
*
*   The class accepts a view and a model, which are used to react to selection changes. This class is able to propagate selection changes
*   to and receive from its surrounding class.
*
*   The model-view-pair can be added as a selection listener to a selection service. This should be done by using 'AddPostSelectionListener'
*   with the existing selection service of the surrounding 'QmitkAbstractView'.
*   The model-view-pair can be set as a selection provider. This should be done by using 'SetAsSelectionProvider' with the existing
*   selection provider of the surrounding 'QmitkAbstractView'.
*
*   The 'QmitkModelViewSelectionConnector' offers a public slot and signal that can be used to set / propagate the selected
*   nodes in the current view:
*   The 'SetCurrentSelection'-slot finds the indices of the given selected nodes in its internal data storage model and
*   changes the selection of the accordingly.
*   The 'CurrentSelectionChanged'-signal sends a list of selected nodes to it's environment.
*   The 'CurrentSelectionChanged'-signal is emitted by the 'ChangeModelSelection'-function, which transforms the internal item view's
*   selection into a data node list. The 'ChangeModelSelection'-function is called whenever the selection of the item view's
*   selection model changes.
*/
class MITK_QT_COMMON QmitkModelViewSelectionConnector : public QObject
{
  Q_OBJECT

public:

  QmitkModelViewSelectionConnector();
  /*
  * @brief Set the view whose selection model is used to propagate or receive selection changes. Use the view's data model
  *        to transform selected nodes into model indexes and vice versa.
  *
  * @pre    The view's data model needs to be a 'QmitkAbstractDataStorageModel'. If so, the data model is received from
  *         the view and stored as a private member.
  *         The data model must return 'mitk::DataNode::Pointer' objects for model indexes if the role is 'QmitkDataNodeRole'.
  * @throw  mitk::Exception, if the view is invalid or the view's data model is not a valid 'QmitkAbstractDataStorageModel'.
  *
  * @par	view	The view to set.
  */
  void SetView(QAbstractItemView* view);

Q_SIGNALS:
  /*
  * @brief A signal that will be emitted by the 'ChangeModelSelection'-function. This happens if the selection model
  *   of the private member item view has changed.
  *
  * @par	nodes		A list of data nodes that are newly selected.
  */
  void CurrentSelectionChanged(QList<mitk::DataNode::Pointer> nodes);

public Q_SLOTS:
  /*
  * @brief Change the selection modus of the item view's selection model.
  *
  *   If true, an incoming selection will be filtered (reduced) to only those nodes that are visible by the current view.
  *   An outgoing selection can then at most contain the filtered nodes.
  *   If false, the incoming non-visible selection will be stored and later added to the outgoing selection,
  *   to include the original selection that could not be modified.
  *   The part of the original selection, that is non-visible are the nodes that are not
  *
  * @par selectOnlyVisibleNodes   The bool value to define the selection modus.
  */
  void SetSelectOnlyVisibleNodes(bool selectOnlyVisibleNodes);
  /*
  * @brief Transform a list of data nodes into a model selection and set this as a new selection of the
  *        selection model of the private member item view.
  *
  *   The function filters the given list of nodes according to the 'm_SelectOnlyVisibleNodes' member variable. If
  *   necessary, the non-visible nodes are stored. This is done if 'm_SelectOnlyVisibleNodes' is false: In this case
  *   the selection may be filtered and only a subset of the selected nodes may be visible and therefore (de-)selectable
  *   in the data storage viewer. By storing the non-visible nodes it is possible to send the new, modified selection
  *   but also include the selected nodes from the original selection that could not be modified (see 'SetSelectOnlyVisibleNodes').
  *
  * @par	nodes		A list of data nodes that should be newly selected.
  */
  void SetCurrentSelection(QList<mitk::DataNode::Pointer> selectedNodes);

private Q_SLOTS:
  /*
  * @brief Transform a model selection into a data node list and emit the 'CurrentSelectionChanged'-signal.
  *
  *   The function adds the selected nodes from the original selection that could not be modified, if
  *   'm_SelectOnlyVisibleNodes' is false.
  *   This slot is internally connected to the 'selectionChanged'-signal of the selection model of the private member item view.
  *
  * @par	selected	The newly selected items.
  * @par	deselected	The newly deselected items.
  */
  void ChangeModelSelection(const QItemSelection& selected, const QItemSelection& deselected);

private:

  QmitkAbstractDataStorageModel* m_Model;
  QAbstractItemView* m_View;

  bool m_SelectOnlyVisibleNodes;
  QList<mitk::DataNode::Pointer> m_NonVisibleSelection;

  /*
  * @brief 	Retrieve the currently selected nodes from the selection model of the private member item view by
  *         transforming the selection indexes into a data node list.
  *
  *   In order to transform the indices into data nodes, the private data storage model must return
  *   'mitk::DataNode::Pointer' objects for model indexes if the role is QmitkDataNodeRole.
  */
  QList<mitk::DataNode::Pointer> GetSelectedNodes() const;
  /*
  * @brief Filter the list of given nodes such that only those nodes are used that are valid
  *        when using the data storage model's node predicate.
  *        If no node predicate was set or the data storage model is invalid, the input list
  *        of given nodes is returned.
  */
  QList<mitk::DataNode::Pointer> FilterNodeList(const QList<mitk::DataNode::Pointer>& nodes) const;
  /*
  * @brief Return true, if the nodes in the list of given selected nodes are equal to the
  *        currently selected nodes from the selection model of the private member item view.
  */
  bool IsEqualToCurrentSelection(QList<mitk::DataNode::Pointer>& selectedNodes) const;

};

#endif // QMITKMODELVIEWSELECTIONCONNECTOR_H