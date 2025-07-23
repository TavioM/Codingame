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
    eprintln!("get_dist [{}:{}] [{}:{}] {}", pos_a.x, pos_a.y, pos_b.x, pos_b.y, (cmp::max(pos_a.x, pos_b.x) - cmp::min(pos_a.x, pos_b.x)) + (cmp::max(pos_a.y, pos_b.y) - cmp::min(pos_a.y, pos_b.y)));
    return (cmp::max(pos_a.x, pos_b.x) - cmp::min(pos_a.x, pos_b.x)) + (cmp::max(pos_a.y, pos_b.y) - cmp::min(pos_a.y, pos_b.y))
}

fn get_closest(agents: & Vec<Agent> , ag: &Agent) -> i32
{
    eprintln!("get_close");
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

fn get_score(p: Coords, grid: &Vec<Tile>, agents: &Vec<Agent>, width: i32, my_id: i32) -> i32
{
    let mut score = 0;

    eprintln!("get_score");
    for x in -1..2
    {
        for y in -1..2
        {
            let t: Vec<_> = agents.iter()
                .filter(|t| t.pos.x == grid[(p.y * width + p.x) as usize].pos.x + x && t.pos.y == grid[(p.y * width + p.x) as usize].pos.y + y)
                .cloned().collect();
            score += t.len() as i32;
            if t.len() > 0 && t[0].player == my_id
            {
                score -= 10;
            }
        }
    }
    eprintln!("get_score_out {}", score);
    return score
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
            grid.extend([Tile{pos: Coords {x, y}, cover: tile_type,}]);
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
        for a in 0..agent_count as usize
        {
            let tile_1: Coords = Coords {x:2, y:2};
            let tile_2: Coords = Coords {x:2, y:9};
            let tile_3: Coords = Coords {x:width - 3, y:2};
            let tile_4: Coords = Coords {x:width - 3, y:height - 3};
            //eprintln!("agent[{}]: {:?}", j, agents[j]);

            if agents[a].player == my_id
            {
                if agents[a].pos.x < 5 || agents[a].pos.x > width - 5
                {
                    println!("HUNKER_DOWN; MESSAGE I'll do nothing");
                }
                else
                {
                    eprintln!("if");
                    if get_score(tile_1, &grid, &agents, width, my_id) > 4
                    {
                        eprintln!("agent[{}]: {:?}", a, agents[a]);
                        if get_dist(&tile_1, &agents[a].pos) > 4
                        {
                            println!("MOVE 5 3");
                        }
                        else
                        {
                            println!("THROW 2 2");
                        }
                    }
                    else if get_score(tile_2, &grid, &agents, width, my_id) > 4
                    {
                        eprintln!("else if");
                        if get_dist(&tile_2, &agents[a].pos) > 5
                        {
                            println!("MOVE 5 8");
                        }
                        else
                        {
                            println!("MOVE 5 8; THROW 2 9");
                        }
                    }
                    else if get_score(tile_3, &grid, &agents, width, my_id) > 4
                    {
                        eprintln!("else if 2");
                        if get_dist(&tile_3, &agents[a].pos) > 5
                        {
                            println!("MOVE {} 3", width - 6);
                        }
                        else
                        {
                            println!("MOVE {} 3; THROW {} 2", width - 6, width - 3);
                        }
                    }
                    else if get_score(tile_4, &grid, &agents, width, my_id) > 4
                    {
                        eprintln!("else");
                        if get_dist(&tile_4, &agents[a].pos) > 5
                        {
                            println!("MOVE {} {}", width - 6, height - 4);
                        }
                        else
                        {
                            println!("MOVE {} {}; THROW {} {}", width - 6, height - 4, width - 3, height - 3);
                        }
                    }
                    else
                    {
                        println!("HUNKER_DOWN; MESSAGE why am I here ?")
                    }
                }
            }
        }
    }
}
