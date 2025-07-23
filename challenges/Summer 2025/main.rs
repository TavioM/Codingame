use std::io;
use std::cmp;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

#[derive(Debug, Copy, Clone)]
struct Coords
{
    x: i32,
    y: i32,
}

#[derive(Debug, Copy, Clone)]
struct Agent
{
    id: i32,
    player: i32,
    pos: Coords,
    cooldown: i32, // Number of turns before this agent can shoot
    splash_bombs: i32,
    wetness: i32, // Damage (0-100) this agent has taken
    optimal_range: i32, // Maximum manhattan distance for greatest damage output
    soaking_power: i32, // Damage output within optimal conditions
    alive: bool,
}

#[derive(Debug, Copy, Clone)]
struct Tile
{
    pos: Coords,
    cover: i32,
}

fn set_dead(ag: &mut Vec<Agent>)
{
    for i in 0..ag.len()
    {
        ag[i].alive = false;
    }
}

fn remove_dead(ag: &mut Vec<Agent>)
{
    ag.retain_mut(|i| i.alive == true);
}

fn update_agent(agents: &mut Vec<Agent>, id: i32, x: i32, y: i32, cooldown: i32, splash_bombs: i32, wetness: i32)
{
    let mut i: usize = 0;
    while agents[i].id != id
    {
        i += 1;
    }
    agents[i].pos.x = x;
    agents[i].pos.y = y;
    agents[i].cooldown = cooldown;
    agents[i].splash_bombs = splash_bombs;
    agents[i].wetness = wetness;
    agents[i].alive = true;
}

fn get_dist(pos_a: &Coords, pos_b: &Coords) -> i32
{
    return
    (cmp::max(pos_a.x, pos_b.x) - cmp::min(pos_a.x, pos_b.x))
    + (cmp::max(pos_a.y, pos_b.y) - cmp::min(pos_a.y, pos_b.y))
}

fn get_closest(agents: & Vec<Agent> , ag: &Agent) -> i32
{
//    let mut close = agents.iter().filter(|t| t.)
    let mut dist: i32 = 420;
    let mut id: i32 = -1;
    for i in 0..agents.len()
    {
        if agents[i].player == ag.player
        {    
            continue
        }
        let tmp = get_dist(&ag.pos, &agents[i].pos);
        if tmp < dist
        {
            dist = tmp;
            id = agents[i].id;
        }
    }
    return id
}

fn main() {
    let mut debug = 1;
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let my_id = parse_input!(input_line, i32); // Your player id (0 or 1)
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let agent_count = parse_input!(input_line, i32); // Total number of agents in the game
    let mut agents: Vec<Agent> = vec![];
    for i in 0..agent_count as usize {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let inputs = input_line.split(" ").collect::<Vec<_>>();
        let id = parse_input!(inputs[0], i32); // Unique identifier for this agent
        let player = parse_input!(inputs[1], i32); // Player id of this agent
        let shoot_cooldown = parse_input!(inputs[2], i32); // Number of turns between each of this agent's shots
        let optimal_range = parse_input!(inputs[3], i32); // Maximum manhattan distance for greatest damage output
        let soaking_power = parse_input!(inputs[4], i32); // Damage output within optimal conditions
        let splash_bombs = parse_input!(inputs[5], i32); // Number of splash bombs this can throw this game
        agents.extend([Agent{id, player, pos: Coords {x: -1, y: -1}, cooldown: shoot_cooldown,
            splash_bombs, wetness: 0, optimal_range, soaking_power, alive: true}]);
    }
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let inputs = input_line.split(" ").collect::<Vec<_>>();
    let mut width = parse_input!(inputs[0], i32); // Width of the game map
    let mut height = parse_input!(inputs[1], i32); // Height of the game map
    let mut grid: Vec<Tile> = vec![];
    for i in 0..height as usize
    {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let inputs = input_line.split_whitespace().collect::<Vec<_>>();
        for j in 0..width as usize
        {
            let x = parse_input!(inputs[3*j], i32); // X coordinate, 0 is left edge
            let y = parse_input!(inputs[3*j+1], i32); // Y coordinate, 0 is top edge
            let tile_type = parse_input!(inputs[3*j+2], i32);
            grid.extend([Tile{pos: Coords {x: x, y: y}, cover: tile_type,}]);
        }
    }

    // game loop
    loop {
        set_dead(&mut agents);
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let agent_count = parse_input!(input_line, i32);
        for i in 0..agent_count as usize {
            let mut input_line = String::new();
            io::stdin().read_line(&mut input_line).unwrap();
            let inputs = input_line.split(" ").collect::<Vec<_>>();
            let id = parse_input!(inputs[0], i32);
            let x = parse_input!(inputs[1], i32);
            let y = parse_input!(inputs[2], i32);
            let cooldown = parse_input!(inputs[3], i32); // Number of turns before this agent can shoot
            let splash_bombs = parse_input!(inputs[4], i32);
            let wetness = parse_input!(inputs[5], i32); // Damage (0-100) this agent has taken
            update_agent(&mut agents, id, x, y, cooldown, splash_bombs, wetness);
        }
        remove_dead(&mut agents);
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let my_agent_count = parse_input!(input_line, usize); // Number of alive agents controlled by you
        eprintln!("agents {}, mine {}, len {}", agent_count, my_agent_count, agents.len());
        for j in 0..agent_count as usize
        {
            //eprintln!("agent[{}]: {:?}", j, agents[j]);
            if agents[j].player == my_id
            {
                let mut aim = Coords {x: -1, y: -1,};
                let mut aim_value: i32 = -1;
                for i in 1..grid.len()
                {
                    let mut temp: i32 = -1;
                    for x in -1..1
                    {
                        for y in -1..1
                        {
                            if grid[i].pos.x + x < 0 || grid[i].pos.y + y < 0 || grid[i].pos.x + x >= width || grid[i].pos.y + y >= height
                            {
                                //eprintln!("stop {} {} | {} {} | {}", grid[i].pos.x, grid[i].pos.y, x, y, i);
                                continue
                            }
                            let t: Vec<_> = agents.iter().filter(|t| t.pos.x == grid[i].pos.x + x && t.pos.y == grid[i].pos.y + y)
                                .cloned().collect();
                            temp += t.len() as i32;
                            //eprintln!("{}:{} {}", x, y, t.len());
                            if t.len() > 0 && t[0].player == my_id
                            {
                                temp -= 10;
                            }
                        }
                    }
                    if temp > aim_value
                    {
                        aim.x = grid[i].pos.x;
                        aim.y = grid[i].pos.y;
                        aim_value = temp;
                        eprintln!("verif aim {}:{}", aim.x, aim.y);
                    }
                }
                eprintln!("{}: {:?}", agents[j].id, aim);
                if get_dist(&agents[j].pos, &aim) <= 2
                {
                    let t: Vec<_> = agents.iter().filter(|t| t.pos.x == agents[j].pos.x && t.pos.y == agents[j].pos.x).cloned().collect();
                    println!("HUNKER_DOWN");
                    //println!("SHOOT {}", t[0].id);
                }
                else if get_dist(&agents[j].pos, &aim) <= 4 && agents[j].splash_bombs > 0
                {
                    println!("THROW {} {}", aim.x, aim.y);
                }
                else if agents[j].splash_bombs > 0
                {
                    let tmp_x = aim.x;
                    let tmp_y = aim.y;
                    while get_dist(&agents[j].pos, &aim) > 4
                    {
                        eprintln!("debug 2, {}:{}", aim.x, aim.y);
                        if (agents[j].pos.x - aim.x).abs() > (agents[j].pos.y - aim.y).abs()
                        {
                            if agents[j].pos.x < aim.x
                            {
                                aim.x -= 1;
                            }
                            else
                            {
                                aim.x += 1;
                            }
                        }
                        else
                        {
                            if agents[j].pos.y < aim.y
                            {
                                aim.y -= 1;
                            }
                            else
                            {
                                aim.y += 1;
                            }
                        }
                    }
                    println!("MOVE {} {}; THROW {} {}", tmp_x, tmp_y, aim.x, aim.y);
                }
                else
                {
                    let close = get_closest(&agents, &agents[j]);
                    let t: Vec<_> = agents.iter().filter(|t| t.id == close).cloned().collect();
                    if get_dist(&agents[j].pos, &t[0].pos) <= 2
                    {
                        //println!("SHOOT {}", t[0].id);
                        println!("HUNKER_DOWN");
                        continue
                    }
                    else if get_dist(&agents[j].pos, &t[0].pos) <= agents[j].optimal_range
                    {
                        println!("THROW {} {}", t[0].pos.x, t[0].pos.y);
                        continue
                    }
                    else
                    {
                        println!("MOVE {} {}", t[0].pos.x, t[0].pos.y);
                        continue
                    }
                }
            }
        }
    }
}

   //             eprintln!("tmp: {:?}", tmp[0]);
    //            if get_dist(&agents[j], &tmp[0]) <= 2
     //           {
      //              println!("SHOOT {}", tmp[0].id);
       //             continue
        //        }
         //       if get_dist(&agents[j], &tmp[0]) <= agents[j].optimal_range
          //      {
           //         println!("THROW {} {}", tmp[0].pos.x, tmp[0].pos.y);
            //        continue
             //   }
              //  else
               // {
                //    println!("MOVE {} {}", tmp[0].pos.x, tmp[0].pos.y);
                 //   continue
                //}
