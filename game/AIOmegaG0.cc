#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME OmegaG0


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  const vector<Dir> dirs = {Bottom, BR, Right, RT, Top, TL, Left, LB};

  typedef vector<int> VI;
  typedef vector<vector<pair<Pos,Dir>>> MPrev;
  typedef vector<vector<bool>> MVis;

  /////////////////////////////////////// FUNCIONS AUXILIARS ///////////////////////////////////////

  bool pos_ok_bfs(Pos& op, int n, Pos& np){
    return (np.i >= op.i-n and np.i <= op.i+n and np.j >= op.j-n and np.j <= op.j+n);
  }

  // Comprova si hi ha perill en un radi r de la pos p
  bool bfs_perill(Pos& p, int r, int i){
    int nf = rows();
    int nc = cols();
    vector<vector<bool>> visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;

    Pos orig = p;
    Q.push(orig);

    while(not Q.empty()){
      Pos np = Q.front();
      Q.pop();

      for (auto d : dirs){
        Pos aux = np+d;
        if (pos_ok(aux) and pos_ok_bfs(orig, r, aux) and cell(aux).type != Rock and not visitat[aux.i][aux.j]){
          int idc = cell(aux).id;
          if (idc != -1){
            if (unit(idc).type == UnitType(i) and unit(idc).player != me()) return true;
          }
          else {
            Q.push(aux);
            visitat[aux.i][aux.j] = true;
          }
        }
      }
    }
    return false;
  }
 
  Dir get_dir2(Pos& op, MPrev& prev, Pos& lp){
    if (prev[lp.i][lp.j].first == op) return prev[lp.i][lp.j].second;
    else return get_dir2(op, prev, prev[lp.i][lp.j].first);
  }

  bool obstacle_furyans(Pos& p){
    int idc = cell(p).id;
    if (idc != -1 and (unit(idc).type == Furyan or unit(idc).type == Pioneer) and unit(idc).player == me()) return true;
    else return false;
  }

  bool obstacle_pionners(Pos& p){
    int idc = cell(p).id;
    if (idc != -1){
      if (unit(idc).type == Furyan and unit(idc).player == me()) return true;
      else if (unit(idc).type == Pioneer) return true;
      else return false;
    }
    return false;
  }

  bool obstacle_fugir(Pos& p){
    int idc = cell(p).id;
    if (idc != -1 and unit(idc).type == Pioneer and unit(idc).player != me()) return true;
    else return false;    
  }

  //Retorna el numero de furyans enemics
  int NFuryan_enemics(Pos& p){
    int cont = 0;
    for (auto d: dirs){
      int id = cell(p+d).id;
      if (id != -1){
        if (unit(id).type == Furyan and unit(id).player != me()) ++cont;
      }
    }
    return cont;
  }

  int nb_pioneers_enem_adj(Pos& p, Dir& nd){
    int cont = 0;
    int minHealth = 101;
    for (auto d : dirs){
      Pos aux = p+d;
      int id = cell(aux).id;
      if (id != -1 and not bfs_perill(p, 2, Hellhound)){
        if (unit(id).type == Pioneer and  unit(id).player != me()){
          ++cont;
          if(unit(id).health < minHealth){
            minHealth = unit(id).health;
            nd = d;
          }
        }
      }
    }
    return cont;
  }

  int NPionners_enemigs(Pos& p, Dir& nd){
    int cont = 0;
    int minHealth = 101;
    for (auto d : dirs){
      int id = cell(p+d).id;
      if (id != -1){
        if (unit(id).type == Pioneer and unit(id).player != me()){
          ++cont;
          if (unit(id).health < minHealth){
            minHealth = unit(id).health;
            nd = d;
          }
        }
      }
    }
    return cont;
  } 

  Dir get_dir_dist(Pos& op, MPrev& prev, Pos& lp, int& ndist){
    ndist = 0;
    bool end = false;
    int f, c;
    while (not end){
      ++ndist;
      f = lp.i;
      c = lp.j;
      if (prev[f][c].first == op) end = true;
      else lp = prev[f][c].first;
    }
    return prev[f][c].second;
  }  

  /////////////////////////////////////// FUNCIONS SUPERFICIE ///////////////////////////////////////

  bool sotaSol(Pos& p, int nr){
    int iniSol = (40+(round()+nr)*2)%80;
    int fiSol = (iniSol+39)%80;

    if (p.j < iniSol){
      if ((iniSol-p.j) <= 2) return true;
    }

    if (iniSol < fiSol) return (p.j >= iniSol and p.j <= fiSol);
    else return (p.j >= iniSol and p.j <= 79) or (p.j >= 0 and p.j <= fiSol);
  }

  bool sotaSolNext(Pos& op, Pos& np, int nr){
    int nx = abs(op.j-np.j);
    int iniSolx = (40+(round()+nr+nx)*2)%80;
    int fiSolx = (iniSolx+39)%80;

    int ny = abs(op.i - np.i);
    int iniSoly = (40+(round()+nr+ny)*2)%80;
    int fiSoly = (iniSoly+39)%80;

    bool bx;
    bool by;

    if (iniSolx < fiSolx) bx = (np.j >= iniSolx and np.j <= fiSolx);
    else bx = (np.j >= iniSolx and np.j <= 79) or (np.j >= 0 and np.j <= fiSolx);

    if (iniSoly < fiSoly) by = (np.j >= iniSoly and np.j <= fiSoly);
    else by = (np.j >= iniSoly and np.j <= 79) or (np.j >= 0 and np.j <= fiSoly);

    return bx or by;
  }

  int calc_distSol(Pos& p, int nr){
    int iniSol = (40+(round()+nr)*2)%80;
    int fiSol = (iniSol+39)%80;

    if (fiSol < p.j) return p.j-fiSol+1;
    else return (79-fiSol + p.j);
  }

  Dir bfs_pionners_sup(Pos& p){
    int nf = rows();
    int nc = cols();
    MPrev prev(nf, vector<pair<Pos,Dir>>(nc));
    MVis visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;
    queue<pair<Pos,Dir>> Asc;

    int distSol = calc_distSol(p, 1);
    int distOb;

    Pos orig = p;
    Q.push(orig);
    visitat[orig.i][orig.j] = true;

    if (cell(orig).type == Elevator){
      if (distSol < 2 or bfs_perill(orig, 1, Necromonger) or bfs_perill(orig, 1, Furyan)) return Down;
    }

    while(not Q.empty()){
      Pos np = Q.front();
      Q.pop();

      for (auto d : dirs){
        Pos aux = np+d;
        if (pos_ok(aux) and pos_ok_bfs(orig, distSol, aux) and not visitat[aux.i][aux.j]){
          if (not sotaSol(aux, 0) and not sotaSolNext(orig, aux, 0)){

            if (not bfs_perill(aux, 1, Necromonger) and not bfs_perill(aux, 1, Furyan)){
              int idc = cell(aux).id;
              if (idc == -1 or (idc != -1 and cell(aux).type == Elevator)){

                Q.push(aux);
                prev[aux.i][aux.j].first = np;
                prev[aux.i][aux.j].second = d;
                visitat[aux.i][aux.j] = true;

                if (cell(aux).gem or cell(aux).type == Elevator){
                  Pos posOb = aux;
                  Dir d = get_dir_dist(orig, prev, posOb, distOb);

                  if (cell(aux).type == Elevator){
                    int distSolAsc = calc_distSol(aux, 1);
                    if (distSolAsc/2 >= distOb) Asc.push({aux,d});
                  }
                  else{
                    int distSolGem = calc_distSol(aux, 1);
                    if (distSolGem/2 >= distOb) return d;
                  }
                }
                else{
                  Q.push(aux);
                  visitat[aux.i][aux.j] = true;
                } 
              } 
            }
            else{
              if (cell(aux).type == Elevator){
                int idc = cell(aux).id;
                if (idc == -1){

                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;

                  Pos posOb = aux;
                  Dir d = get_dir_dist(orig, prev, posOb, distOb);

                  int distSolAsc = calc_distSol(aux, 1);
                  if (distSolAsc/2 >= distOb) Asc.push({aux,d});


                }

              }
            }
          }
        }
      }
    }

    if (cell(orig).type == Elevator) return Down;
    if (not Asc.empty()) return Asc.front().second;
    return None;
  }       

  bool bfs_gem_acc(Pos& p, int nr){
    int nf = rows();
    int nc = cols();
    MPrev prev(nf, vector<pair<Pos,Dir>>(nc));
    MVis visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;

    int distSol = calc_distSol(p, nr);
    int distOb;

    Pos orig = p;
    orig.k = 1;
    Q.push(orig);

    while (not Q.empty()){
      Pos np = Q.front();
      Q.pop();

      for (auto d : dirs){
        Pos aux = np+d;

        if (pos_ok(aux) and pos_ok_bfs(orig, distSol, aux) and not visitat[aux.i][aux.j]){
          int idc = cell(aux).id;
          if (idc == -1){
            if (not bfs_perill(aux, 1, Necromonger) and not sotaSol(aux, nr) and cell(aux).id == -1){

              Q.push(aux);
              prev[aux.i][aux.j].first = np;
              prev[aux.i][aux.j].second = d;
              visitat[aux.i][aux.j] = true;

              if (cell(aux).gem){
                Pos posOb = aux;
                Dir d = get_dir_dist(orig, prev, posOb, distOb);

                int distSolGem = calc_distSol(aux, nr);
                if (distSolGem/2 >= distOb) return true;
              }
            }
          }
        }
      }
    }
    return false;
  }

  bool bfs_obj_acc(Pos& p, int nr){
    int nf = rows();
    int nc = cols();
    MPrev prev(nf, vector<pair<Pos,Dir>>(nc));
    MVis visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;

    int distSol = calc_distSol(p, nr);
    int distOb;

    Pos orig = p;
    orig.k = 1;
    Q.push(orig);

    while (not Q.empty()){
      Pos np = Q.front();
      Q.pop();

      for (auto d : dirs){
        Pos aux = np+d;
        if (pos_ok(aux) and pos_ok_bfs(orig, distSol, aux) and not visitat[aux.i][aux.j] and not sotaSol(aux, nr) and not obstacle_furyans(aux)){
            
          Q.push(aux);
          prev[aux.i][aux.j].first = np;
          prev[aux.i][aux.j].second = d;
          visitat[aux.i][aux.j] = true;

          int idc = cell(aux).id;
          if (idc != -1){
            if (unit(idc).type == Pioneer or unit(idc).type == Furyan){
              Pos posOb = aux;
              Dir d = get_dir_dist(orig, prev, posOb, distOb);
              int distSolUni = calc_distSol(aux, nr);
              if (distSolUni/2 >= distOb) return true;

            }
          }
        }
      }
    }
    return false;
  }

  /////////////////////////////////////// FUNCIONS COVA ///////////////////////////////////////

  bool elev_adj(Pos& p){
    for (auto d : dirs){
      Pos aux = p+d;
      if (pos_ok(aux) and cell(aux).type != Rock){
        int idc = cell(aux).id;
        if (idc == -1){
          if (not bfs_perill(aux, 2, Hellhound) and not bfs_perill(aux, 2, Furyan)){
            if (cell(aux).type == Elevator) return true;
          }
        }
      }
    }
    return false;
  }
  
  Dir bfs_pionners_cave(Pos& p){
    int nf = rows();
    int nc = cols();
    MPrev prev(nf, vector<pair<Pos,Dir>>(nc));
    MVis visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;

    Pos orig = p;
    Q.push(orig);
    visitat[orig.i][orig.j] = true; 

    while(not Q.empty()){
      Pos np = Q.front();
      Q.pop();

      for (auto d : dirs){
        Pos aux = np+d;
        if (pos_ok(aux) and cell(aux).type != Rock and not visitat[aux.i][aux.j]){
          int idc = cell(aux).id;
          if (idc == -1){
            if (not bfs_perill(aux, 2, Hellhound) and not bfs_perill(aux, 2, Furyan)){

              Q.push(aux);
              prev[aux.i][aux.j].first = np;
              prev[aux.i][aux.j].second = d;
              visitat[aux.i][aux.j] = true;

              if (cell(aux).owner != me() and cell(aux).type == Cave and cell(aux).owner != -1) return get_dir2(orig, prev, aux);
              if (cell(aux).type == Elevator){
                int distOb;
                Pos lp = aux;
                Dir d = get_dir_dist(orig, prev, lp, distOb);
                if (bfs_gem_acc(aux, distOb+1)) return get_dir2(orig, prev, aux);
              }
            }
          }
        }
      }
    }

    Dir ld = None;
    for (auto d : dirs){
      Pos aux = orig+d;
      if (pos_ok(aux) and cell(aux).type == Cave){
        int idc = cell(aux).id;
        if (idc == -1 and not bfs_perill(aux, 2, Hellhound)){
          ld = d;
          if (not bfs_perill(aux, 1, Furyan)) return d;
        }
      }
    }
    return ld;
  }

  Dir bfs_furyans_cave(Pos& p){
    int nf = rows();
    int nc = cols();
    MPrev prev(nf, vector<pair<Pos,Dir>>(nc));
    MVis visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;
    int id = cell(p).id;


    if (NFuryan_enemics(p) == 1 and unit(id).health > 35){
      if (not bfs_perill(p, 2, Hellhound)){
        for (auto d : dirs){
          Pos aux = p+d;
          int idc = cell(aux).id;
          if (idc != -1 and unit(idc).type == Furyan and unit(idc).player != me()) return d;
        }
      }
    }

    Pos orig = p;
    Q.push(orig);
    visitat[orig.i][orig.j] = true; 

    while(not Q.empty()){
      Pos np = Q.front();
      Q.pop();

      for (auto d : dirs){
        Pos aux = np+d;

        if (pos_ok(aux) and cell(aux).type != Rock and not visitat[aux.i][aux.j]){
          if (not bfs_perill(aux, 5, Hellhound) and not obstacle_furyans(aux)){
            if (unit(id).health > 35){
              if (NFuryan_enemics(orig) > 1){
                if (not bfs_perill(aux, 1, Furyan)){
                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;

                  int idc = cell(aux).id;
                  if (idc != -1 and unit(idc).player != me()){
                    if (unit(idc).type == Pioneer){
                      if (prev[aux.i][aux.j].first != orig) return get_dir2(orig, prev, aux);
                    }
                    else if (unit(idc).type == Furyan){
                      if (prev[aux.i][aux.j].first != orig) return get_dir2(orig, prev, aux);
                    }
                  }

                }
              }
              else{
                if (not bfs_perill(orig, 1, Furyan)){

                  if (bfs_perill(np, 2, Hellhound)){
                    if(not obstacle_fugir(aux)){
                      Q.push(aux);
                      prev[aux.i][aux.j].first = np;
                      prev[aux.i][aux.j].second = d;
                      visitat[aux.i][aux.j] = true;
                    }
                  }
                  else{
                    Q.push(aux);
                    prev[aux.i][aux.j].first = np;
                    prev[aux.i][aux.j].second = d;
                    visitat[aux.i][aux.j] = true;

                    int idc = cell(aux).id;
                    if (idc != -1 and unit(idc).player != me() and unit(idc).type == Pioneer) return get_dir2(orig, prev, aux);   
                  }
                  
                }
                else{

                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;

                  int idc = cell(aux).id;
                  if (idc != -1 and unit(idc).player != me() and unit(idc).type == Furyan) return get_dir2(orig, prev, aux);      
                }
              }
            }
            else if (unit(id).health <= 35){
              if (bfs_perill(np, 1, Furyan)){
                if (not bfs_perill(aux, 1, Furyan) and not obstacle_fugir(aux)){

                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;   
                              
                }
              }
              else {
                if (not bfs_perill(aux, 1, Furyan)){

                  if (bfs_perill(np, 2, Hellhound)){
                    if(not obstacle_fugir(aux)){
                      Q.push(aux);
                      prev[aux.i][aux.j].first = np;
                      prev[aux.i][aux.j].second = d;
                      visitat[aux.i][aux.j] = true;
                    }
                  }
                  else{
                    Q.push(aux);
                    prev[aux.i][aux.j].first = np;
                    prev[aux.i][aux.j].second = d;
                    visitat[aux.i][aux.j] = true;

                    int idc = cell(aux).id;
                    if (idc != -1 and unit(idc).player != me() and unit(idc).type == Pioneer) return get_dir2(orig, prev, aux);   
                  }

                }
              }
            }
          }
        }
      }
    }
    if (bfs_perill(orig, 1, Furyan)){
      for (auto d: dirs){
        int id = cell(orig+d).id;
        if (id != -1){
          if (unit(id).type == Furyan and unit(id).player != me()) return d;
        }
      }
    }
    else if (bfs_perill(orig, 1, Pioneer)){
      for (auto d: dirs){
        int id = cell(orig+d).id;
        if (id != -1){
          if (unit(id).type == Pioneer and unit(id).player != me()) return d;
        }
      }    
    }
    return None;
  }   

  /////////////////////////////////////// FUNCIONS PRINCIPALS ///////////////////////////////////////  

  void move_pioneers() {
    vector<int> P = pioneers(me());

    int iniSol = (40+round()*2)%80;
    int fiSol = (iniSol+39)%80;


    for (int id : P){
      Pos p = unit(id).pos;
      if (p.k == 0){
        if (cell(p).type == Elevator){
          Pos aux = p;
          aux.k = 1;
          if (not sotaSol(aux, 1) and not bfs_perill(aux, 1, Necromonger) and bfs_gem_acc(aux, 1)){
            command(id, Up);
          }
          else{
            Dir nd = bfs_pionners_cave(p);
            command(id, nd);
          }
        }
        else{
          Dir nd = bfs_pionners_cave(p);
          command(id, nd);
        }
      }
      else{
        Dir nd = bfs_pionners_sup(p);
        command(id, nd);
      }

    }
  }

  void atacando_p(Pos& p){
    int idc = cell(p).id;
    if (idc != -1 and unit(idc).type == Pioneer and unit(idc).player != me()) cerr << "ATACANDO PIONEER" << endl;
  } 

  void atacando_f(Pos& p){
    int idc = cell(p).id;
    if (idc != -1 and unit(idc).type == Furyan and unit(idc).player != me()) cerr << "ATACANDO FURIAN, SALUD ENEM: " << unit(idc).health << endl;
  }

  void move_furyans(){
    vector<int> F = furyans(me());
    int nfur = F.size();
    for (int id : F){
      Pos p = unit(id).pos;
      Dir nd = bfs_furyans_cave(p);
      Pos aux = p+nd;
      command(id, nd);
    }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move_furyans();
    move_pioneers();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
