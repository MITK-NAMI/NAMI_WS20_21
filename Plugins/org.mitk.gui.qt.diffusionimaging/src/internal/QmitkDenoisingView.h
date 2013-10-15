/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef _QMITKQmitkDenoisingView_H_INCLUDED
#define _QMITKQmitkDenoisingView_H_INCLUDED

#include <berryISelectionListener.h>

#include <QmitkFunctionality.h>

#include "ui_QmitkDenoisingViewControls.h"

#include <itkVectorImage.h>
#include <itkImage.h>
#include <mitkDiffusionImage.h>
#include <itkOrientationDistributionFunction.h>
#include <mitkQBallImage.h>
#include <vtkTransform.h>
#include <vtkDoubleArray.h>
#include <vtkOdfSource.h>
#include <vtkSmartPointer.h>
#include <QmitkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <itkDiffusionTensor3D.h>

/*!
  \brief View displaying details of the orientation distribution function in the voxel at the current crosshair position.

  \sa QmitkFunctionality
  \ingroup Functionalities
*/

class QmitkDenoisingView : public QmitkFunctionality
{
  // this is needed for all Qt objects that should have a Qt meta-object
  // (everything that derives from QObject and wants to have signal/slots)
  Q_OBJECT

public:

  static const std::string VIEW_ID;

  QmitkDenoisingView();
  virtual ~QmitkDenoisingView();

  typedef float TOdfPixelType;
  typedef itk::Vector<TOdfPixelType,QBALL_ODFSIZE> OdfVectorType;
  typedef itk::Image<OdfVectorType,3> OdfVectorImgType;

  typedef itk::DiffusionTensor3D< TOdfPixelType >  TensorPixelType;
  typedef itk::Image< TensorPixelType, 3 >         TensorImageType;

  virtual void CreateQtPartControl(QWidget *parent);

  virtual void StdMultiWidgetAvailable (QmitkStdMultiWidget &stdMultiWidget);
  virtual void StdMultiWidgetNotAvailable();

  void OnSliceChanged(const itk::EventObject& e);

protected slots:

protected:

  /// \brief called by QmitkFunctionality when DataManager's selection has changed
  virtual void OnSelectionChanged( std::vector<mitk::DataNode*> nodes );

  void UpdateOdf(); ///< called if slice position or datamanager selection has changed

  Ui::QmitkDenoisingViewControls*  m_Controls;
  QmitkStdMultiWidget*              m_MultiWidget;

  /** observer flags */
  int m_SliceObserverTag1;
  int m_SliceObserverTag2;
  int m_SliceObserverTag3;
  int m_PropertyObserverTag;

  /** ODF related variables like mesh structure, values etc. */
  vtkPolyData*                      m_TemplateOdf;  ///< spherical base mesh
  vtkSmartPointer<vtkTransform>     m_OdfTransform;
  vtkSmartPointer<vtkDoubleArray>   m_OdfVals;
  vtkSmartPointer<vtkOdfSource>     m_OdfSource;

  int                               m_OdfNormalization; ///< normalization method defined in the visualization view

  /** rendering of the ODF */
  vtkActor*                     m_VtkActor;
  vtkPolyDataMapper*            m_VtkMapper;
  vtkRenderer*                  m_Renderer;
  vtkRenderWindow*              m_VtkRenderWindow;
  vtkRenderWindowInteractor*    m_RenderWindowInteractor;
  vtkCamera*                    m_Camera;

  mitk::DataNode::Pointer m_ImageNode;
};



#endif // _QmitkDenoisingView_H_INCLUDED
