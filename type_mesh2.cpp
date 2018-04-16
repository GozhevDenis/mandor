///** \file type_mesh2.c
//  * \brief Set of routines to manipulate with unrolled arrays using reg_t map to access elements of the storage array.
//  */
//
//#include <stdlib.h> 
//
//#include "type_mesh2.h"
//
//#include "log.h"
//#include "misc_cfgReader.h"
//
//// ---------------------------------------------------------------------------
///// Saves map and header to the file.
//// ---------------------------------------------------------------------------
//void
//mesh2_save (const char *name, const reg_t *saveReg, const reg_t *map, const char *array, int elemSize)
//{
//  int min[3] = {saveReg.getMin()[0]*MC_X, saveReg.getMin()[1]*MC_Y, saveReg.getMin()[2]*MC_Z};  //metod *MC_X
//  int max[3] = {saveReg.getMax()[0]*MC_X, saveReg.getMax()[1]*MC_Y, saveReg.getMax()[2]*MC_Z};
//
//  ENSURE (reg_isInside (saveReg, map), "save region is bigger than domain");
//
//  FILE *fp = CFG_OPEN (name, "wb");										// Opens file.
//  int span = (max[2] - min[2] + 1);											// Defines size of the continuous chunk.
//  for (int i = min[0] ; i <= max[0] ; ++i)										// Saves body of the mesh.
//    for (int j = min[1] ; j <= max[1] ; ++j)
//      fwrite (array + elemSize*mf_mesh2_offset(map, i, j, min[2]), elemSize, span, fp);
//
//  fwrite (ACTIVATOR, sizeof (int), 3, fp);
//  fwrite (min, sizeof (int), 3, fp);											// Saves region boundaries and so on.
//  fwrite (max, sizeof (int), 3, fp);
//  fwrite (&elemSize, sizeof (int), 1, fp);
//  fclose (fp);														// Closes file.
//}
//
//// ---------------------------------------------------------------------------
///// \brief Loads entire mesh and updates mapper to access loaded data. Pointer to the allocated array is returned.
//// ---------------------------------------------------------------------------
//void*
//mesh2_load (const char *name, reg_t *map, int *elemSize)
//{
//  int activator[3];
//  FILE *fp = CFG_OPEN (name, "rb");					// Opens file.
//
//  fseek (fp, -10*sizeof (int), SEEK_END);					// Gets info added to the tail of file.
//  fread (activator, sizeof (int), 3, fp);
//  fread (map->min, sizeof (int), 3, fp);					// Loads region limits.
//  fread (map->max, sizeof (int), 3, fp);          // ИЗМЕНИТЬ ЧЕРЕЗ КЛАСС
//  fread (elemSize, sizeof (int), 1, fp);
//
//  ENSURE (activator[0] == MC_X
//       && activator[1] == MC_Y
//       && activator[2] == MC_Z,
//          "inconsistent dimensionality of the simulation");
//
//  mf_mesh_initUnroll (map);
//
//  const int volume = map.volume();
//  void *array = malloc ((*elemSize)*volume);
//  ENSURE (array, "cannot allocate %.3f Kb", (*elemSize)*volume/1024.0);
//
//  fseek (fp, 0, SEEK_SET);							// Gets body of the array.
//  fread (array, *elemSize, volume, fp);
//  fclose (fp);
//
//  return array;
//}
//
//// ---------------------------------------------------------------------------
///// \brief Takes array and map and updates old-style mesh. This function is to ease transition to the new type and will be removed with old mesh type.
//// ---------------------------------------------------------------------------
//void
//mesh2_mesh (reg_t *map, void *array, int elemSize, mesh_p mesh)
//{
//  int sizeX, sizeY, sizeZ;
//
//  mesh->imin = MC_X*map.getMin()[0];
//  mesh->jmin = MC_Y*map.getMin()[1];
//  mesh->kmin = MC_Z*map.getMin()[2];
//  mesh->imax = MC_X*map->getMax()[0];
//  mesh->jmax = MC_Y*map->getMax()[1];
//  mesh->kmax = MC_Z*map->getMmax()[2];
//
//  switch (elemSize)
//  {
//    case sizeof (double):
//      mesh->type = 0;
//    break;
//
//    case sizeof (vec3D_t):
//      mesh->type = 1;
//    break;
//
//    default:
//      DIE ("bad elemSize (%d)", elemSize);
//    break;
//  }
//
//  /* Assignes axis limits and applies boundary degeneracy rules. */
//  sizeX = mesh->imax - mesh->imin + 1;
//  sizeY = mesh->jmax - mesh->jmin + 1;
//  sizeZ = mesh->kmax - mesh->kmin + 1;
//
//  /* Updates memory management parameters. */
//  mesh->width_z = sizeZ;
//  mesh->width_yz = sizeY*sizeZ;
//  mesh->size = sizeX*sizeY*sizeZ*elemSize;
//
//  if (mesh->storage)
//    free (mesh->storage);
//  mesh->storage = array;
//
//  switch (mesh->type)
//  {
//    case mc_double:
//      mesh->origin = mesh->storage;
//      mesh->origin = (void *) (& (mv_f(mcast_meshDouble (mesh), -mesh->imin, -mesh->jmin, -mesh->kmin)));
//    break;
//
//    case mc_vec3D_t:
//      mesh->origin = mesh->storage;
//      mesh->origin = (void *) (& (mv_v(mcast_meshVec (mesh), -mesh->imin, -mesh->jmin, -mesh->kmin)));
//    break;
//  }
//
//  strcpy (mesh->name, "converted");
//}
