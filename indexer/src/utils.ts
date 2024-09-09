import { Event } from "./modules/types"

export const getPubkeys = (event: Event): string[] => {
    let pubkeys = event.tags.map((tag: any) => { 
        if(tag[1].length < 64) return null;

        if(tag[1].includes(":")) {
            tag[1] = tag[1]
                .substring(tag[1].indexOf(":") + 1, 
                    tag[1].lastIndexOf(":"))
        } 

        return tag[1];
    });

    return pubkeys.filter((f: string) => f != null)
}




