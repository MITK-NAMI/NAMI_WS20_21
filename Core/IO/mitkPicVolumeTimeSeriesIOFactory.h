/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __mitkPicVolumeTimeSeriesIOFactory_h
#define __mitkPicVolumeTimeSeriesIOFactory_h

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#include "itkObjectFactoryBase.h"
#include "mitkBaseData.h"

namespace mitk
{
//##Documentation
//## @brief Create instances of PicVolumeTimeSeriesReader objects using an object factory.
//##
//## @ingroup IO
class PicVolumeTimeSeriesIOFactory : public itk::ObjectFactoryBase
{
public:  
  /** Standard class typedefs. */
  typedef PicVolumeTimeSeriesIOFactory   Self;
  typedef itk::ObjectFactoryBase  Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;
  
  /** Class methods used to interface with the registered factories. */
  virtual const char* GetITKSourceVersion(void) const;
  virtual const char* GetDescription(void) const;
    
  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);
  static PicVolumeTimeSeriesIOFactory* FactoryNew() { return new PicVolumeTimeSeriesIOFactory;}
  /** Run-time type information (and related methods). */
  itkTypeMacro(PicVolumeTimeSeriesIOFactory, ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  {
    PicVolumeTimeSeriesIOFactory::Pointer PicVolumeTimeSeriesIOFactory = PicVolumeTimeSeriesIOFactory::New();
    ObjectFactoryBase::RegisterFactory(PicVolumeTimeSeriesIOFactory);
  }
  
protected:
  PicVolumeTimeSeriesIOFactory();
  ~PicVolumeTimeSeriesIOFactory();

private:
  PicVolumeTimeSeriesIOFactory(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};
  
  
} // end namespace mitk

#endif
