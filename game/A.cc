#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Gamma


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

  const vector<Dir> dirs = {Bottom, BR, Right, RT, Top, TL, Left, LB, None};

  typedef vector<int> VI;
  typedef vector<vector<pair<Pos,Dir>>> MPrev;
  typedef vector<vector<bool>> MVis;

  /////////////////////////////////////// FUNCIONS AUXILIARS ///////////////////////////////////////

  bool pos_ok_bfs(Pos& op, int n, Pos& np){
    return (np.i >= op.i-n and np.i <= op.i+n and np.j >= op.j-n and np.j <= op.j+n);
  }

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
        // miramos que aux este en el tablero y que el BFS no vaya más alla de donde queremos
        // que aux no sea una roca, y que la casilla ya no este vistada
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

  Dir get_dir(Pos& op, MPrev& prev, Pos& lp){
    bool end = false;
    int f, c;
    while (not end){
      f = lp.i;
      c = lp.j;
      if (prev[f][c].first == op) end = true;
      else lp = prev[f][c].first;
    }
    return prev[f][c].second;
  }

  bool obstacle_furyans(Pos& p){
    int idc = cell(p).id;
    if (idc != -1 and (unit(idc).type == Furyan or unit(idc).type == Pioneer) and unit(idc).player == me()) return true;
    else return false;
  }

  bool obstacle_fugir(Pos& p){
    int idc = cell(p).id;
    if (idc != -1 and unit(idc).type == Pioneer and unit(idc).player != me()) return true;
    else return false;    
  }

  int NFuryan_enemigs(Pos& p){
    int cont = 0;
    for (auto d: dirs){
      int id = cell(p+d).id;
      if (id != -1){
        if (unit(id).type == Furyan and unit(id).player != me()) ++cont;
      }
    }
    return cont;
  }

  int NPionners_enemigs(Pos& p, Dir& nd){
    int cont = 0;
    int minHealth = 101;
    for (auto d: dirs){
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

  /////////////////////////////////////// FUNCIONS SUPERFICIE ///////////////////////////////////////

  Dir get_dir_sup(Pos& op, MPrev& prev, Pos& lp, int& ndist){
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

    //TRUE SI LA POS ESTARA BAJO EL SOL EN LA SIGUIENTE RONDA
  bool sotaSol(Pos& p){
    int iniSol = (42+round()*2)%80;
    int fiSol = (iniSol+39)%80;
    return (p.j >= iniSol and p.j <= fiSol);
  }
  
  int calc_distSol(Pos& p){
    int iniSol = (42+round()*2)%80;
    int fiSol = (iniSol+39)%80;

    if (fiSol < p.j) return p.j-fiSol;
    else return (79-fiSol + p.j);
  }

  Dir bfs_pionners_sup(Pos& p){
    int nf = rows();
    int nc = cols();
    vector<vector<pair<Pos,Dir>>> prev(nf, vector<pair<Pos,Dir>>(nc));
    vector<vector<bool>> visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;
    queue<pair<Pos,Dir>> Asc;

    int distSol = calc_distSol(p);
    int ndist = 0;

    Pos orig = p;
    Q.push(orig);
    visitat[orig.i][orig.j] = true;

    if (cell(orig).type == Elevator){
      if (distSol < 2 or bfs_perill(orig, 1, Necromonger)) return Down;
    }

    if (distSol < 2 and cell(orig).type == Elevator) return Down; 

    while(not Q.empty()){
      Pos np = Q.front();
      Q.pop();
      //cerr << "POP DE LA PILA: " << np << endl;

      for (auto d : dirs){
        Pos aux = np+d;
        if (pos_ok(aux) and pos_ok_bfs(orig, distSol, aux) and not visitat[aux.i][aux.j]){
          int idc = cell(aux).id;
          if (idc == -1){
            if (not bfs_perill(aux, 1, Necromonger) and not sotaSol(aux) and cell(aux).id == -1){
              
              //cerr << "AÑADIDO A LA PILA: " << aux << endl;

              Q.push(aux);
              prev[aux.i][aux.j].first = np;
              prev[aux.i][aux.j].second = d;
              visitat[aux.i][aux.j] = true;



              if (cell(aux).gem or cell(aux).type == Elevator){
                Pos cop = aux;
                //ndist -> numero de pasos hasta una gema o un ascensor
                Dir d = get_dir_sup(orig, prev, cop, ndist);

                if (cell(aux).type == Elevator){
                  //me guardo la pos del ascensor i la direccion a tomar desde np
                  Asc.push({aux,d});
                }
                else if (cell(aux).gem){
                  if (ndist > distSol-1){
                    // la gema esta muy lejos voy al ascensor más cercano
                    return Asc.front().second;
                  }
                  else return d;
                }
              }
            }
          }
        }
      }
    }
    return None;
  }   

  /////////////////////////////////////// FUNCIONS COVA ///////////////////////////////////////  

  Dir bfs_pionners_cave(Pos& p){
    int nf = rows();
    int nc = cols();
    vector<vector<pair<Pos,Dir>>> prev(nf, vector<pair<Pos,Dir>>(nc));
    vector<vector<bool>> visitat(nf, vector<bool>(nc, false));
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

              if (cell(aux).owner != me() and cell(aux).type != Elevator) return get_dir(orig, prev, aux);
            }
          }
        }
      }
    }
    return None;
  }

  Dir bfs_furyans_cave(Pos& p){
    int nf = rows();
    int nc = cols();
    MPrev prev(nf, vector<pair<Pos,Dir>>(nc));
    MVis visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;

    Pos orig = p;
    Q.push(orig);
    int id = cell(orig).id;
    visitat[orig.i][orig.j] = true; 

    while(not Q.empty()){
      Pos np = Q.front();
      //cerr << "POP DE LA PILA: " << np << endl;
      Q.pop();

      for (auto d : dirs){
        Pos aux = np+d;

        if (pos_ok(aux) and cell(aux).type != Rock and not visitat[aux.i][aux.j]){
          if (not bfs_perill(aux, 3, Hellhound) and not obstacle_furyans(aux)){
            if (unit(id).health > 30){
              //cerr << "VIDA > 30" << endl;
              //tengo 2 o mas furias adjacentes
              if (NFuryan_enemigs(orig) > 1){
                if (not bfs_perill(aux, 1, Furyan)){
                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;

                  int idc = cell(aux).id;

                  if (idc != -1 and unit(idc).player != me()){
                    if (unit(idc).type == Pioneer){
                      //no atacos a pioners que estan en pos adjacentes, ya tengo furias adjacentes
                      if (prev[aux.i][aux.j].first != orig) return get_dir(orig, prev, aux);
                    }
                    else if (unit(idc).type == Furyan){
                      //no ataco furias adjacentes
                      if (prev[aux.i][aux.j].first != orig) return get_dir(orig, prev, aux);
                    }
                  }

                }
              }
              // tengo 1 o ningun furia adjacente
              else{
                //no hay ningun furian
                if (not bfs_perill(orig, 1, Furyan)){

                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;

                  int idc = cell(aux).id;
                  if (idc != -1 and unit(idc).player != me() and unit(idc).type == Pioneer) return get_dir(orig, prev, aux);
                }
                // hay un furia
                else{

                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;

                  int idc = cell(aux).id;
                  if (idc != -1 and unit(idc).player != me() and unit(idc).type == Furyan) return get_dir(orig, prev, aux);      
                }
              }
            }
            else if (unit(id).health <= 30){
              //cerr << "VIDA <= 30" << "HUIR" << endl;
              if (bfs_perill(np, 1, Furyan)){
                if (not bfs_perill(aux, 1, Furyan) and not obstacle_fugir(aux)){

                  //cerr << "Pos a la pila: " << aux << endl;
                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;   
                              
                }
              }
              //NO tengo Furyans enemigos en mis pos ADJ
              else {
                if (not bfs_perill(aux, 1, Furyan)){

                  //cerr << "Pos a la pila: " << aux << endl;
                  Q.push(aux);
                  prev[aux.i][aux.j].first = np;
                  prev[aux.i][aux.j].second = d;
                  visitat[aux.i][aux.j] = true;   

                  int idc = cell(aux).id;
                  if (idc != -1 and unit(idc).type == Pioneer and unit(idc).player != me()) return get_dir(orig, prev, aux);           
                }
              }
            }
          }
        }
      }
    }
    return None;
  }   

  /////////////////////////////////////// FUNCIONS PTINCIPALS ///////////////////////////////////////  

  void move_pioneers() {
    vector<int> P = pioneers(me());

    int iniSol = (42+round()*2)%80;
    int fiSol = (iniSol+39)%80;

    for (int id : P){
      Pos p = unit(id).pos;
      if (p.k == 0){
        if (cell(p).type == Elevator){
          Pos aux = p;
          aux.k = 1;
          if (not sotaSol(aux) and not bfs_perill(aux, 1, Necromonger)) command(id, Up);
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
      //estoy en la superficie
      else{
        //cerr << string(15,'*') << endl;
        //cerr << "FUERA" << endl;
        //cerr << "ROUND: " << round() << " " << "MI ID: " << id << endl;
        //cerr << "COLUMNA SOL: " << fiSol << endl;
        //cerr << "DISTANCIA A SOL: " << calc_distSol(p) << endl;
        //cerr << "POS ACTUAL: " << p << endl;
        //cerr << "MI SALUD: " << unit(cell(p).id).health << endl;
        Dir nd = bfs_pionners_sup(p);
        //cerr << "NUEVA POS " << p+nd << endl;
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
    if (idc != -1 and unit(idc).type == Furyan and unit(idc).player != me()) cerr << "ATACANDO FURIAN" << endl;
  }

  void move_furyans(){
    vector<int> F = furyans(me());
    //int id = F[4];
    for (int id : F){
      Pos p = unit(id).pos;
      //cerr << string(15,'*') << endl;
      //cerr << "ROUND: " << round() << " " << "MI ID: " << id << endl;
      //cerr << "POS ACTUAL: " << p << endl;
      //cerr << "MI SALUD: " << unit(cell(p).id).health << endl;
      //if (bfs_perill(p, 1 ,Furyan)) cerr << "FURIA ENEM POS ADJ" << endl;
      Dir nd = bfs_furyans_cave(p);
      Pos aux = p+nd;
      //cerr << "NUEVA POS " << p+nd << endl;
      //atacando_p(aux);
      //atacando_f(aux);
      //cerr << string(15,'*') << endl;
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
