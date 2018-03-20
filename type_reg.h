//text\
//#include <vector>

#ifndef MC_TYPE_REG_HEADER
#define MC_TYPE_REG_HEADER 			//need to fix?

class reg_t
{
	int min[3];			///< Corner of the region with minimal coordinates.
	int max[3];			///< Corner of the region with maximal coordinates.
	int cpu;			///< Cpu number of the object owner / shift of the origin used to map reg_t::min to the beginning of the unrolled array.
	int barcode;		///< Auxilary information tagged by creator to travel with the region.
	int wrap[3];		///< Wrapping of the region (used to trace the shift of region due to periodicity) / strides for the mesh.
	public:
		reg_t(int [3], int [3], int, int , int [3]);
		reg_t(int, int, int, int, int, int, int, int, int, int, int);
		reg_t(int [3], int [3]);
		reg_t(int, int, int, int, int, int);
		reg_t();
		const char * printRanges();
		const char * printCorners();
		const int * getMin();
		const int getMin(int);
		const int * getMax();
		const int getMax(int);
		const int * getWrap();
		const int getWrap(int);
		const int getCpu();
		const int getBarcode();
		void setMin(int, int, int);
		void setMin(int, int);	
		void setMax(int, int, int);
		void setMax(int, int);
		void setWrap(int, int, int);
		void setWrap(int, int);
		// TODO setCPU, setBarcode
		void unwrap();
		long long volume();
		//int overlap(const reg_t &, const reg_t &)		TODO 
		void collapse();
		int operator <= (const reg_t &); 
};
//TODO
///#define mc_reg_init     {0, 0, 0,  0, 0, 0,  0, 0,   0, 0, 0}                 ///< reg_t init constants (all zeroes).
///#define mc_reg_initBad  {-1, -1, -1,  -5, -5, -5,  -1, -1,   -1, -1, -1}      ///< reg_t init (badly sorted to corrupt everything if used).
///#define mc_regList_init {0, 0}                                                  ///< regList_t defaults (\b realloc is used => NULL pointer \b must be start value).

/*#define mf_reg_collapse(reg)
{
  (reg).setMin((reg).getMin()[0]*MC_X, (reg).getMin()[1]*MC_Y, (reg).getMin()[0]*MC_Z)
  (reg).setMax((reg).getMax()[0]*MC_X, (reg).getMax()[1]*MC_Y, (reg).getMax()[0]*MC_Z)
  (reg).setWrap((reg).getWrap()[0]*MC_X, (reg).getWrap()[1]*MC_Y, (reg).getWrap()[0]*MC_Z)                                                                           \
}*/

/**
  * \brief Group of regions. Used to hold regions for processing, passing and so on. Field \b list is a pointer to reallocatable memory chunk.
  */

class regList_t
{
	std::vector<reg_t> list;
	public:
		const int getSize();
		void push_back(const reg_t&);
		void clear();
		void slice(int, int);
		const int verify();
		//TODO function for change reg
		//TODO const metod
};
#endif
