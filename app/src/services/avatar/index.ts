import hashprint from 'hashprintjs'

export const generateAvatar = async (displayName: string) => {
    
    const dataURL = await hashprint({ data: displayName, size: 200 });

    return dataURL
}

export const getInitials = (displayName: string) => {
    return displayName.split(" ").map(word => word[0].toUpperCase()).join()
}
