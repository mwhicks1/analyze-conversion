









#define SEED1 793
#define SEED2 39
#define SEED3 17

#include "em3d.h"
#include "util.h"


extern int NumNodes;
int NumMisses;

int n_nodes;
int d_nodes;
int local_p;

node_t * * make_table(int size, int procname)  {
  node_t * * retval  = calloc(size, sizeof(node_t *));
  if (!retval) { puts("Assertion failure"); exit(-1); };
  return retval;
}


void fill_table(node_t * * node_table , double * values , int size, int procname)
{
  node_t * cur_node = ((void*)0);
  node_t * prev_node = ((void*)0);
  int i;

  prev_node = calloc(1, sizeof(node_t));
  node_table[0] = prev_node;
  *values = gen_uniform_double();
   { prev_node->value = values++; }
  prev_node->from_count = 0;


  for (i=1; i<size; i++) {
    cur_node = calloc(1, sizeof(node_t));
    *values = gen_uniform_double();
     { cur_node->value = values++; }
    cur_node->from_count = 0;
    node_table[i] = cur_node;
    prev_node->next = cur_node;
    prev_node = cur_node;
  }
  cur_node->next = ((void*)0);
}

void make_neighbors(node_t * nodelist, table_arr_t * table , int tablesz,
      int degree, int percent_local, int id)
{
  node_t * cur_node = nodelist;

  for(; cur_node; cur_node=cur_node->next) {
    node_t * other_node = ((void*)0);
    int j,k;
    int dest_proc;

    node_t * * tmp  = calloc(degree, (sizeof(node_t *)));
    ;

    cur_node->degree = degree;
     { cur_node->to_nodes = tmp; }

    for (j=0; j<degree; j++) {
      do {
        node_t * * local_table  = ((void*)0);
        int number = gen_number(tablesz);

        if (check_percent(percent_local)) {
          dest_proc = id;
        } else {
          dest_proc = (id + 1 + 4*gen_signed_number(1)) % 1;
        }


         { local_table = table[dest_proc].table; }
        other_node = local_table[number];
        if (!other_node) {
           { printf("Error! on dest %d @ %d\n",number,dest_proc); };
          exit(1);
        }

        node_t * * ub = tmp + j;
 node_t * * tmp2  = 0;
  { tmp2 = tmp; }
        for ( ; tmp2 < ub; tmp2++)
          if (other_node == *tmp2) break;
        k = tmp2 - tmp;




#if 0



#endif
      }

      while (k<j);

      if (!cur_node || !cur_node->to_nodes) {
         { printf("Error! no to_nodes filed!\n"); };
        exit(1);
      }

      cur_node->to_nodes[j] = other_node;
#if 0


#endif
      ++other_node->from_count;
    }
  }
}

void update_from_coeffs(node_t * nodelist) {
  node_t * cur_node = nodelist;


  for (; cur_node; cur_node=cur_node->next) {
    int from_count = cur_node->from_count;

    if (from_count < 1) {
       { printf("Help! no from count (from_count=%d) \n", from_count); };
      cur_node->from_values = calloc(20, sizeof(double *));
      cur_node->coeffs = calloc(20, sizeof(double));
      cur_node->from_length = 0;
    } else {
      cur_node->from_values = calloc(from_count, sizeof(double *));
      cur_node->coeffs = calloc(from_count, sizeof(double));
      cur_node->from_length = 0;
    }
  }
}

void fill_from_fields(node_t * nodelist, int degree) {
  node_t * cur_node = nodelist;
  for(; cur_node; cur_node = cur_node->next) {
    int j;

    for (j=0; j<degree; j++) {
      int count,thecount;
      node_t * other_node = cur_node->to_nodes[j];
      double * * otherlist  = ((void*)0);
      double * value = cur_node->value;

      if (!other_node) {  { printf("Help!!\n"); }; }
      count=(other_node->from_length)++;
       { otherlist=other_node->from_values; }
      thecount=other_node->from_count;
      if (!otherlist) {


         { otherlist = other_node->from_values; }

      }

      otherlist[count] = value;


      other_node->coeffs[count]=gen_uniform_double();
    }
  }
}

void localize_local(node_t * nodelist) {
  node_t * cur_node = nodelist;

  for(; cur_node; cur_node = cur_node->next) {
    cur_node->coeffs = cur_node->coeffs;
    cur_node->from_values = cur_node->from_values;
    cur_node->value = cur_node->value;
  }
}


void make_tables(table_t * table,int groupname) {
  node_t * * h_table  = ((void*)0);
  node_t * * e_table  = ((void*)0);
  double * h_values  = ((void*)0);
  double * e_values  = ((void*)0);
  int procname = 0;

  init_random(793*groupname);
  h_values = calloc(n_nodes/1, sizeof(double));
  h_table = make_table(n_nodes/1,procname);
  fill_table(h_table,h_values,n_nodes/1,procname);
  e_values = calloc(n_nodes/1, sizeof(double));
  e_table = make_table(n_nodes/1,procname);
  fill_table(e_table,e_values,n_nodes/1,procname);



  table->e_table[groupname].size = n_nodes/1;
  table->h_table[groupname].size = n_nodes/1;
   { table->e_table[groupname].table = e_table; }
   { table->h_table[groupname].table = h_table; }
}

void make_all_neighbors(table_t * table,int groupname) {
  node_t * first_node = ((void*)0);
  int local_table_size = 1;
  int local_table_bounds = local_table_size;
  node_t * * local_table  = ((void*)0);
  table_arr_t * local_table_array  = ((void*)0);

  init_random(39*groupname);

  local_table_size = table->h_table[groupname].size;
   { local_table = table->h_table[groupname].table; }
   { local_table_array = table->e_table; }
  first_node = local_table[0];
  make_neighbors(first_node,
   local_table_array,n_nodes/1,
   d_nodes,local_p,groupname);

  local_table_size = table->e_table[groupname].size;
   { local_table = table->e_table[groupname].table; }
   { local_table_array = table->h_table; }
  first_node = local_table[0];
  make_neighbors(first_node,
   local_table_array,n_nodes/1,
   d_nodes,local_p,groupname);
}

void update_all_from_coeffs(table_t * table, int groupname)
{
  int local_table_size = 1;
  int local_table_bounds = local_table_size;
  node_t * * local_table  = ((void*)0);
  node_t * first_node = ((void*)0);


  local_table_size = table->h_table[groupname].size;
   { local_table = table->h_table[groupname].table; }

  first_node = local_table[0];
  update_from_coeffs(first_node);

  local_table_size = table->e_table[groupname].size;
   { local_table = table->e_table[groupname].table; }
  first_node = local_table[0];
  update_from_coeffs(first_node);
}

void fill_all_from_fields(table_t * table, int groupname)
{
  int local_table_size = 1;
  int local_table_bounds = local_table_size;
  node_t * * local_table  = ((void*)0);
  node_t * first_node = ((void*)0);

  init_random(17*groupname);
  local_table_size = table->h_table[groupname].size;
   { local_table = table->h_table[groupname].table; }
  first_node = local_table[0];
  fill_from_fields(first_node,d_nodes);

  local_table_size = table->e_table[groupname].size;
   { local_table = table->e_table[groupname].table; }
  first_node = local_table[0];
  fill_from_fields(first_node,d_nodes);
}

void localize(table_t * table, int groupname)
{
  int local_table_size = 1;
  int local_table_bounds = local_table_size;
  node_t * * local_table  = ((void*)0);
  node_t * first_node = ((void*)0);

  local_table_size = table->h_table[groupname].size;
   { local_table = table->h_table[groupname].table; }
  first_node = local_table[0];
  localize_local(first_node);

  local_table_size = table->e_table[groupname].size;
   { local_table = table->e_table[groupname].table; }
  first_node = local_table[0];
  localize_local(first_node);
}

void clear_nummiss(table_t * table, int groupname)
{
  NumMisses = 0;
}

void do_all(table_t * table, int groupname, int nproc,
     void(*func)(table_t * ,int), int groupsize) {

  if (nproc > 1) {
    do_all(table,groupname+nproc/2,nproc/2,func,groupsize);
    do_all(table,groupname,nproc/2,func,groupsize);
  } else {
    func(table,groupname);
  }
}

graph_t * initialize_graph(void) {
  table_t * table = ((void*)0);
  graph_t * retval = ((void*)0);
  int i,j,blocksize;
  int groupsize;

  table = calloc(1, sizeof(table_t));
  retval = calloc(1, sizeof(graph_t));

  groupsize = 1/NumNodes;

   { printf("making tables \n"); };
  do_all(table,0,1,make_tables,groupsize);



   { printf("making neighbors\n"); };

  do_all(table,0,1,make_all_neighbors,groupsize);


   { printf("updating from and coeffs\n"); };
  do_all(table,0,1,update_all_from_coeffs,groupsize);


   { printf("filling from fields\n"); };
  do_all(table,0,1,fill_all_from_fields,groupsize);

   { printf("localizing coeffs, from_nodes\n"); };
  do_all(table,0,1,localize,groupsize);

  blocksize = 1/NumNodes;

   { printf("cleanup for return now\n"); };
  for (i=0; i<NumNodes; i++) {
    int local_table_size = table->e_table[i*blocksize].size;
    int local_table_bounds = local_table_size;
    node_t * * local_table  = ((void*)0);
     { local_table = table->e_table[i*blocksize].table; }
    node_t * local_node_r = local_table[0];

    retval->e_nodes[i] = local_node_r;

    local_table_size = table->h_table[i*blocksize].size;
     { local_table = table->h_table[i*blocksize].table; }
    local_node_r = local_table[0];
    retval->h_nodes[i] = local_node_r;
    for (j = 1; j < blocksize; j++) {
      node_t * local_node_l = ((void*)0);

      local_table_size = table->e_table[i*blocksize+j-1].size;
       { local_table = table->e_table[i*blocksize+j-1].table; }
      local_node_l = (node_t *)local_table[(n_nodes/1)-1];
      local_table_size = table->e_table[i*blocksize+j].size;
       { local_table = table->e_table[i*blocksize+j].table; }
      local_node_r = local_table[0];
      local_node_l->next = local_node_r;

      local_table_size = table->h_table[i*blocksize+j-1].size;
       { local_table = table->h_table[i*blocksize+j-1].table; }
      local_node_l = (node_t *)local_table[(n_nodes/1)-1];
      local_table_size = table->h_table[i*blocksize+j].size;
       { local_table = table->h_table[i*blocksize+j].table; }
      local_node_r = local_table[0];
      local_node_l->next = local_node_r;
    }
  }

   { printf("Clearing NumMisses\n"); };
  do_all(table,0,1,clear_nummiss,groupsize);
   { printf("Returning\n"); };

  return retval;
}
